#include "cd.h"

void cd(sysStatus * pstatus, char * cmdstr, char * pwd)
{
	char * i;
	int to;
	char filename[1025];

	if ( '\0' == cmdstr[0] || '\n' == cmdstr[0] )
	{
		printf(">>> cd [foldername]\n"
			">>> Please enter the name of a folder in the present working directory\n");
		return ;
	}
	else
	{
		sscanf(cmdstr, "%s", filename);
		to = checkExist(pstatus, filename);
		if ( ! strcmp("..", filename) )
		{
			pstatus->pwd = pstatus->fcbs[pstatus->pwd].dadFCB;
			for ( i = pwd+strlen(pwd)-1; *i != '/'; i -- )
			{
				*i = 0;
			}
			if ( pstatus->pwd )
			{
				*i = 0;
			}
			return ;
		}
		else if ( ! strcmp("/", filename) )
		{
			pstatus->pwd = 0;
			sprintf(pwd, "/");
		}
		else if ( -1 == to )
		{
			printf("\033[31m>>> Name does not exist!\033[0m\n");
			return ;
		}
		else
		{
			if ( ! pstatus->fcbs[to].flagFoder )
			{
				printf("\033[31m>>> Not a folder!\033[0m\n");
				return ;
			}
			if ( pstatus->pwd )
			{
				strcpy(pwd+strlen(pwd), "/");
				strcpy(pwd+strlen(pwd), pstatus->fcbs[to].filename);
			}
			else
			{
				strcpy(pwd+strlen(pwd), pstatus->fcbs[to].filename);
			}
			pstatus->pwd = to;
			return ;
		}
	}

	return ;	
}
