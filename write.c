#include "write.h"

void writeChar(sysStatus * pstatus, int i, char ch)
{
	int block, moveby, blockID;
	block = i / contentSize;
	moveby = i - block * contentSize;
	if ( -1 == pstatus->fcbs[pstatus->pwd].nextIB )
	{
		blockID = pstatus->fcbs[pstatus->pwd].nextIB = newIB(pstatus);
		writeFCB(pstatus, pstatus->pwd);
	}
	else
	{
		for ( blockID = pstatus->fcbs[pstatus->pwd].nextIB; 
				block -- && pstatus->ibs[blockID].nextIB != -1; 
				blockID = pstatus->ibs[blockID].nextIB 
		);
		if ( ! block )
		{
			// * blockID = newIB(pstatus);	
			writeIBp(pstatus, blockID, newIB(pstatus));
			blockID = pstatus->ibs[blockID].nextIB;
		}
	}
	pstatus->disk[512*(64+ blockID)+moveby+sizeof(int)] = ch;
	return ;
}

void write(sysStatus * pstatus, char * cmdstr)
{
	int begin = 0, p, i, length;
	char buf[1024];
	long * endplong = (long*) buf;
	sscanf(cmdstr, "%d", &begin);
	if ( begin > pstatus->fcbs[pstatus->pwd].size )
	{
		begin = pstatus->fcbs[pstatus->pwd].size;
		printf("\033[33m>>> Request out of range!\033[0m\n");
	}
	printf(">>> Writing starts from %d\n", begin);
	p = begin;
	printf("\033[32m>>> end with <F12><Enter> in one line\033[0m\n");
	while ( True )
	{
		printf("<<< ");
		memset(buf, 0, sizeof(buf));
		fgets(buf, 1024, stdin);
		if (
			( 8 == sizeof(long) && *endplong == 11537157872411 ) || 
			( 4 == sizeof(long) && *endplong == 875715355 )
		)
		{
			break;
		}
		length = strlen(buf);
		for ( i = 0; i < length; p ++, i ++ )
		{
			writeChar(pstatus, p, buf[i]);
		}
	}
	if ( p > pstatus->fcbs[pstatus->pwd].size )
	{
		pstatus->fcbs[pstatus->pwd].size = p;
	}
	writeFCB(pstatus, pstatus->pwd);
	return ;
}
