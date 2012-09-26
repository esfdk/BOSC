#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "commands.h"

void runcmdls()
{
	DIR *dp;
	struct dirent *ep;
	dp = opendir ("./");
	char filelist[2048];
	
	if(dp != NULL)
	{
		while(ep = readdir (dp))
		{
			strcat(filelist, ep->d_name);
			strcat(filelist, "   ");
			//snprintf(filelist, sizeof(filelist), )
			//puts(ep->d_name);
		}
		
		puts(filelist);
		
		closedir (dp);
	}
	else
	{
		perror("Couldn't open directory");
	}
}
