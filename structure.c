#include "structure.h"

void initFCB(sysStatus * pstatus, int x, boolean flagFoder)
{
	time_t temptime;

	pstatus->free_fcb = pstatus->fcbs[x].nextFCB;
	pstatus->fcbs[x].dadFCB = pstatus->pwd;
	pstatus->fcbs[x].nextFCB = -1;
	pstatus->fcbs[x].subFCB = -1;
	pstatus->fcbs[x].flagFoder = flagFoder;
	time(&temptime);
	pstatus->fcbs[x].create = temptime;
	pstatus->fcbs[x].lastChange = temptime;
	pstatus->fcbs[x].size = 0;
	pstatus->fcbs[x].nextIB = -1;

}

int checkExist(sysStatus * pstatus, char * name)
{
	int i;
	for ( i = pstatus->fcbs[pstatus->pwd].subFCB; i != -1; i = pstatus->fcbs[i].nextFCB )
	{
		if ( ! strcmp(name, pstatus->fcbs[i].filename) )
		{
			return i;
		}
	}
	return -1;
}
