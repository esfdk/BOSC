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
#include "parser.h"
#include "print.h"

/* --- symbolic constants --- */
#define HOSTNAMEMAX 100

/* --- use the /proc filesystem to obtain the hostname --- */
char *getuserandhostname(char *hostname, size_t size)
{
	FILE *hostnamefile;
	char hname[HOSTNAMEMAX];
	char line[HOSTNAMEMAX];
	
	hostnamefile = fopen ("/proc/sys/kernel/hostname", "r");

	while (fgets(line, HOSTNAMEMAX, hostnamefile))
	{
		if(sscanf(line, "%s", hname))
		{
			/* Writes the user and host name to hostname. */
			snprintf(hostname, size, "%s@%s", getenv("USER"), hname); 
		}
	}
  
	return hostname;
}

char *getcurrentdir(char *dir, size_t size)
{
	char cur_path_buffer[1024];
	char *cur_path = getcwd(cur_path_buffer, sizeof(cur_path_buffer));
	snprintf(dir, size, "%s", cur_path);
	return dir;
}

/* --- execute a shell command --- */
int executeshellcmd (Shellcmd *shellcmd)
{
	printshellcmd(shellcmd); /* Prints the shell command(s). Should be removed at some point. */
	
	Cmd *cmdlist = shellcmd->the_cmds;
	
	if (!strcmp(*cmdlist->cmd, "exit")){
		exit(0);
	}
	
	char **cd_command = cmdlist->cmd;
	
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
	}
	
	pid_t pid;
	int *ret_status;
	
	
	
	
	pid = fork();
	
	if (pid)
	{
        pid = wait(ret_status);
	}
	else
	{	
		char** args = cmdlist->cmd;
		
		if(execvp(args[0], args))
		{
			
		}
	}
	
	return 0;
}

/* --- main loop of the simple shell --- */
int main(int argc, char* argv[]) {

	/* initialize the shell */
	char *cmdline;
	char hostname[HOSTNAMEMAX];
	char currentdir[1024];
	int terminate = 0;
	Shellcmd shellcmd;

	if (getuserandhostname(hostname, sizeof(hostname))) 
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
