#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "commands.h"

void runcmdls()
{
	DIR *dp;
	struct dirent *ep;
	dp = opendir ("./");
	
	if(dp != NULL)
	{
		while(ep = readdir (dp))
		{
			puts(ep->d_name);
		}
		
		closedir (dp);
	}
	else
	{
		perror("Couldn't open directory");
	}
}
