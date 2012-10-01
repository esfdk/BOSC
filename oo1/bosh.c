/* bosh.c : BOSC shell */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <signal.h>
#include "parser.h"

/* --- symbolic constants --- */
#define HOSTNAMEMAX 100
#define SHELL_MAX_PROCESSES 50

/* Interupt handler */
static void int_handler(int sig);

/* pid's for the running processes */
pid_t running_foreground_processes[SHELL_MAX_PROCESSES];
pid_t running_background_processes[SHELL_MAX_PROCESSES];

/* Gets user and hostnames and inserts them into a string with the format "user@hostname". */
char *get_user_and_hostname(char *hostname, size_t size)
{
	FILE *hostnamefile;
	char hname[HOSTNAMEMAX];
	char line[HOSTNAMEMAX];
	
	hostnamefile = fopen ("/proc/sys/kernel/hostname", "r");

	while (fgets(line, HOSTNAMEMAX, hostnamefile))
	{
		if(sscanf(line, "%s", hname))
		{
			snprintf(hostname, size, "%s@%s", getenv("USER"), hname); 
		}
	}
  
	return hostname;
}

/* Sets dir to be the current working directory. */
char *getcurrentdir(char *dir, size_t size)
{
	char cur_path_buffer[1024];
	char *cur_path = getcwd(cur_path_buffer, sizeof(cur_path_buffer));
	snprintf(dir, size, "%s", cur_path);
	return dir;
}

/* Executes a shell command. */
int executeshellcmd (Shellcmd *shellcmd)
{	
	if (!strcmp(*shellcmd->the_cmds->cmd, "exit")){
		return 1;
	}
	
	char **cd_command = shellcmd->the_cmds->cmd;
	
	if (strcmp(cd_command[0], "cd") == 0 && cd_command[1] != NULL)
	{
		const char *newdir = cd_command[1];
		int error = chdir(newdir);
		
		switch (error) 
		{
			case 0: break;
			case EACCES: printf("%s: access denied.\n", newdir); break;
			case ENOENT: printf("%s: no such file or directory.\n", newdir); break;
			case ENOTDIR: printf("%s: not a directory.\n", newdir); break;
			default: printf("%s: error %i\n", newdir, error); break;
		}
		
		return 0;
	}
	
	shell_cmd_with_pipes(shellcmd, 0);
	
	return 0;
}

/* Main function for executing shell commands. */
int shell_cmd_with_pipes(Shellcmd *shellcmd, int write_pipe)
{
	int fd[2];
	char **cmd = shellcmd->the_cmds->cmd;
	shellcmd->the_cmds = shellcmd->the_cmds->next;
    int proc_pid;
	
	/* Pipes if the shellcommand has more than one command. */
	if(shellcmd->the_cmds != NULL)
	{
		pipe(fd);
	}
	
	/* Fork process - if parent, just continue. If child, run if.*/
	if(!(proc_pid = fork()))
	{
		if(shellcmd->the_cmds != NULL)
		{
			close(fd[1]);
		}
		
		/* If any commands are left, close stdin and dup pipe.
		   Else if stdin is redirected, close stdin and dup the 
		   stdin file.											*/
		if(shellcmd->the_cmds)
		{
			close(fileno(stdin));
			dup(fd[0]);
		} else if(shellcmd->rd_stdin)
		{
			close(fileno(stdin));
			dup(fileno(fopen(shellcmd->rd_stdin, "r")));
		}
		
		/* If write_pipe is more than 0, close stdin and dup write_pipe.
		   Else if stdout is redirected, close stdout and dup the stdout
		   file.														*/
		if(write_pipe > 0)
		{
			close(fileno(stdout));
			dup(write_pipe);
		} else if(shellcmd->rd_stdout)
		{
			close(fileno(stdout));
			dup(fileno(fopen(shellcmd->rd_stdout, "w+")));
		}
		
		/* If stderr is redirected, close stderr and dup redirected stderr.*/
		if(shellcmd->rd_stderr)
		{
			close(fileno(stderr));
			dup(fileno(fopen(shellcmd->rd_stderr, "w+")));
		}
		
		execvp(cmd[0], cmd);
		printf("Could not find command: %s \n", cmd[0]);
	}

	/* If background process, add proc_pid to list of background
	   processes, else add to foreground processes. 			*/
	if(shellcmd->background)
	{
		add_background_process(proc_pid);
	}
	else
	{
		add_foreground_process(proc_pid);
	}
	
	/* Close write_pipe if it is more than zero. */
	if (write_pipe > 0) 
	{
		close(write_pipe);
	}
	
	/* If more commands are left, close read and run recursively. */
	if(shellcmd->the_cmds != NULL)
	{
		close(fd[0]);
		shell_cmd_with_pipes(shellcmd, fd[1]);
	}
	
	int exit_code;
	/* If shell command is not marked as background, wait for pid. Else
	   do not wait.													*/
	if(!shellcmd->background)
	{
		waitpid(proc_pid, &exit_code, 0);
	}
}

/* Adds a process to list of foreground processes. */
int add_foreground_process(pid_t process)
{
	int i = 0;
	pid_t *proc;
	while(*(proc = &(running_foreground_processes[i])) > 0 && i < SHELL_MAX_PROCESSES) i++;
	
	/* TODO: Should introduce handling too many processes. */
	
	*proc = process;
	
	return 0;
}

/* Adds a process to list of background processes. */
int add_background_process(pid_t process)
{
	int i = 0;
	pid_t *proc;
	while(*(proc = &(running_background_processes[i])) > 0 && i < SHELL_MAX_PROCESSES) i++;
	
	/* TODO: Should introduce handling too many processes. */
	
	*proc = process;
	
	return 0;
}

/* --- main loop of the simple shell --- */
int main(int argc, char* argv[]) {

	/* Handles Cntrl+c input. */
	signal(SIGINT, int_handler);
	
	/* Handles zombie processes. */
	signal(SIGCHLD, SIG_IGN);

	/* initialize the shell */
	char *cmdline;
	char hostname[HOSTNAMEMAX];
	char currentdir[1024];
	int terminate = 0;
	Shellcmd shellcmd;

	if (get_user_and_hostname(hostname, sizeof(hostname))) 
	{
		/* parse commands until exit or ctrl-c */
		while (!terminate) 
		{
			printf("%s:", hostname);
			printf("%s", getcurrentdir(currentdir, sizeof(currentdir)));
			if (cmdline = readline("# ")) 
			{
				if(*cmdline) 
				{
					add_history(cmdline);
					if (parsecommand(cmdline, &shellcmd)) 
					{
						terminate = executeshellcmd(&shellcmd);
					}
				}
			
				free(cmdline);
			} 
			else terminate = 1;
		}
		
		printf("Exiting bosh.\n");
	}    
    
	return EXIT_SUCCESS;
}

/* Interupt handler. Closes all running foreground processes. */
void int_handler(int sig) 
{
	sig = 0;
	int i;
	pid_t *process;
	
	for (i = 0; *(process = &running_foreground_processes[i]) > 0 && i < SHELL_MAX_PROCESSES; i++) 
	{
		kill(*process, SIGINT);
		*process = 0;
	}
}
