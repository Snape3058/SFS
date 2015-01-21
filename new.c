#include "new.h"

void New(
	char * filename, 
	char * cmdstr, 
	char * pwd, 
	sysStatus * pstatus
)
{
	int i;
	time_t temptime;

	if ( pstatus->disk )
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
	pstatus->disk = (char *) malloc (diskSize);
	if ( NULL == pstatus->disk )
	{
		printf("\033[31m>>> malloc failed!\033[0m\n");
		return ;
	}
	/* arrange memory */
	memset(pstatus->disk, 0, diskSize);
	sprintf(pwd, "/");
	/* init system status block */
	for ( i = 0; i < fcbNum; i ++ )
	{
		pstatus->fcbs[i].dadFCB = -1;
		pstatus->fcbs[i].nextFCB = i + 1;
		pstatus->fcbs[i].subFCB = -1;
		pstatus->fcbs[i].nextIB = -1;
	}
	pstatus->fcbs[fcbNum-1].nextFCB = -1;
	pstatus->free_fcb = 0;
	for ( i = 0; i < ibNum; i ++ )
	{
		writeIBp(pstatus, i, i+1);
		pstatus->ibs[i].contentBlockID = 512*(64+i)+sizeof(int);
	}
	writeIBp(pstatus, ibNum-1, -1);
	pstatus->free_ib = 0;
	pstatus->full_fcb = -1;
	// sync();
	pstatus->full_fcb = 0;
	pstatus->pwd = 0;
	initFCB(pstatus, 0, True);
	for ( i = 0; i < fcbNum; i ++ )
	{
		writeFCB(pstatus, i);
	}
	return ;
}

