#include "rmdir.h"

void rmdir(sysStatus * pstatus, char * cmdstr)
{
	char filename[1025];
	int i, * last;


	if ( '\0' == cmdstr[0] || '\n' == cmdstr[0] )
	{
		printf(">>> rmdir [filename]\n"
			">>> Please enter the name of the exist directory.\n");
		return ;
	}
	else
	{
		sscanf(cmdstr, "%s", filename);
	}
	for ( i = pstatus->fcbs[pstatus->pwd].subFCB, last = &(pstatus->fcbs[pstatus->pwd].subFCB); i != -1; last = &(pstatus->fcbs[i].nextFCB), i = pstatus->fcbs[i].nextFCB )
	{
		if ( ! strcmp(filename, pstatus->fcbs[i].filename) )
		{
			if ( ~ pstatus->fcbs[i].subFCB )
			{
				printf("\033[31m>>> Folder is not empry!\033[0m\n");
				return ;
			}
			*last = pstatus->fcbs[i].nextFCB;
			pstatus->fcbs[i].dadFCB = 
			pstatus->fcbs[i].subFCB = -1;
			pstatus->fcbs[i].strlen = 
			pstatus->fcbs[i].size = 0;
			pstatus->fcbs[i].nextFCB = pstatus->free_fcb;
			free(pstatus->fcbs[i].filename);
			pstatus->fcbs[i].filename = NULL;
			pstatus->fcbs[i].create = 0;
			pstatus->fcbs[i].lastChange = 0;
			pstatus->fcbs[i].flagFoder = False;
			pstatus->free_fcb = i;
			return ;
		}
	}
	printf("\033[31m>>> Folder does not exist!\033[0m\n");
	return ;
}
