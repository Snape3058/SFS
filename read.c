#include "read.h"

char readChar(sysStatus * pstatus, int i)
{
	int block, moveby, blockID;
	block = i / contentSize;
	moveby = i - block * contentSize;
	for ( blockID = pstatus->fcbs[pstatus->pwd].nextIB; block --; blockID = pstatus->ibs[blockID].nextIB )
		;
	return pstatus->disk[512*(64+blockID)+moveby+sizeof(int)];
}

void read(sysStatus * pstatus, char * cmdstr)
{
	int i;
	int begin = 0, end = pstatus->fcbs[pstatus->pwd].size;
	sscanf(cmdstr, "%d%d", &begin, &end);
	if ( end > pstatus->fcbs[pstatus->pwd].size )
	{
		end = pstatus->fcbs[pstatus->pwd].size;
		printf("\033[33m>>> Request out of range!\033[0m\n");
	}
	for ( i = begin; i < end; i ++ )
	{
		putchar(readChar(pstatus, i));
	}
	return ;
}
