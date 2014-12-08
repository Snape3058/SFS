#include "new.h"

void New(
	char * filename, 
	char * cmdstr, 
	char * pwd, 
	char ** disk, 
	sysStatus * pstatus
)
{
	int i;
	time_t temptime;

	if ( *disk )
	{
		printf("\033[31m>>> An SFS has already been opened!\033[0m\n");
		return ;
	}
	if ( '\0' == cmdstr[0] || '\n' == cmdstr[0] )
	{
		printf(">>> new [filename]\n"
			">>> Please enter the name of the restore file.\n");
		return ;
	}
	else
	{
		sscanf(cmdstr, "%s", filename);
		printf(">>> SFS restored to: %s\n", filename);
	}
	*disk = (char *) malloc (diskSize);
	if ( NULL == disk )
	{
		printf("\033[31m>>> malloc failed!\033[0m\n");
		return ;
	}
	/* arrange memory */
	memset(*disk, 0, diskSize);
	sprintf(pwd, "/");
	/* init system status block */
	for ( i = 0; i < fcbNum; i ++ )
	{
		pstatus->fcbs[i].nextFCB = i + 1;
		pstatus->fcbs[i].subFCB = -1;
		pstatus->fcbs[i].nextIB = -1;
	}
	pstatus->fcbs[fcbNum-1].nextFCB = -1;
	pstatus->free_fcb = 1;
	for ( i = 0; i < 4096; i ++ )
	{
		pstatus->ibs[i].nextIB = i + 1;
		pstatus->ibs[i].contentBlockID = -1;
	}
	pstatus->ibs[4095].nextIB = -1;
	pstatus->free_ib = 0;
	pstatus->full_fcb = -1;
	// sync();
	pstatus->full_fcb = 0;
	pstatus->pwd = 0;
	pstatus->fcbs[0].nextFCB = -1;
	pstatus->fcbs[0].subFCB = -1;
	pstatus->fcbs[0].flagFoder = True;
	time(&temptime);
	pstatus->fcbs[0].create = temptime;
	pstatus->fcbs[0].lastChange = temptime;
	pstatus->fcbs[0].size = 0;
	pstatus->fcbs[0].nextIB = -1;
	return ;
}

