#include "structure.h"

void initFCB(sysStatus * pstatus, int x, boolean flagFoder)
{
	time_t temptime;

	pstatus->free_fcb = pstatus->fcbs[x].nextFCB;
	pstatus->fcbs[x].nextFCB = -1;
	pstatus->fcbs[x].subFCB = -1;
	pstatus->fcbs[x].flagFoder = flagFoder;
	time(&temptime);
	pstatus->fcbs[x].create = temptime;
	pstatus->fcbs[x].lastChange = temptime;
	pstatus->fcbs[x].size = 0;
	pstatus->fcbs[x].nextIB = -1;

}
