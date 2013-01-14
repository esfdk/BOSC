#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv){
	int id;
	int childstatus;
	if(!(id = fork())){
		execvp(argv[1], &argv[1]);
		printf("command not known");
	}
	wait(&childstatus);
	printf("Program ran its course \n");
	return 0;
}
