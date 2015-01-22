#include "delete.h"

void rm(sysStatus * pstatus, char * cmdstr)
{
	char filename[1025];
	int i, * last;

	if ( '\0' == cmdstr[0] || '\n' == cmdstr[0] )
	{
		printf(">>> delete|rm [filename]\n"
			">>> Please enter the name of the exist file.\n");
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
			if ( pstatus->fcbs[i].flagFoder )
			{
				printf("\033[31m>>> Not a file!\033[0m\n");
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
			freeFCB(pstatus, i);
			writeFCB(pstatus, i);
			clearIB(pstatus, pstatus->fcbs[i].nextIB);
			return ;
		}
	}
	printf("\033[31m>>> File does not exist!\033[0m\n");
	return ;
}
