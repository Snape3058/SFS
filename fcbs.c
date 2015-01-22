#include "fcbs.h"

void fcbs(sysStatus * pstatus, char * cmdstr)
{
	int i, id;
	char * c, * l;
	printf("free_fcb\t:%d\n", pstatus->free_fcb);
	printf("full_fcb\t:%d\n", pstatus->full_fcb);
	printf("ID\t|dadFCB\t|nextFCB|subFCB\t|Folder\t|create date\t\t\t|last change\t\t\t|size\t|nextIB\t|file name\n");
	printf("--------|-------|-------|-------|-------|-------------------------------|-------------------------------|-------|-------|--------\n");
	if ( '\0' == cmdstr[0] || '\n' == cmdstr[0] )
	{
		for ( i = 0; i < fcbNum; i ++ )
		{
			c = ctime(&(pstatus->fcbs[i].create));
			c[strlen(c)-1] = 0;
			l = ctime(&(pstatus->fcbs[i].lastChange));
			l[strlen(l)-1] = 0;
			printf ("%-8d|%d\t|%d\t|%d\t|%s\t|%s\t|%s\t|%d\t|%d\t|%s\n", i,
				pstatus->fcbs[i].dadFCB,
				pstatus->fcbs[i].nextFCB,
				pstatus->fcbs[i].subFCB,
				pstatus->fcbs[i].flagFoder?"True":"False",
				c,
				l,
				pstatus->fcbs[i].size,
				pstatus->fcbs[i].nextIB,
				pstatus->fcbs[i].filename);
		}
	}
	else
	{
		sscanf(cmdstr, "%d", &id);
		c = ctime(&(pstatus->fcbs[id].create));
		c[strlen(c)-1] = 0;
		l = ctime(&(pstatus->fcbs[id].lastChange));
		l[strlen(l)-1] = 0;
		printf ("%-8d|%d\t|%d\t|%d\t|%s\t|%s\t|%s\t|%d\t|%d\t|%s\n", id,
			pstatus->fcbs[id].dadFCB,
			pstatus->fcbs[id].nextFCB,
			pstatus->fcbs[id].subFCB,
			pstatus->fcbs[id].flagFoder?"True":"False",
			c,
			l,
			pstatus->fcbs[id].size,
			pstatus->fcbs[id].nextIB,
			pstatus->fcbs[id].filename);
		printf("[IB]");
		for ( i = pstatus->fcbs[id].nextIB; i != -1 ; i = pstatus->ibs[i].nextIB )
		{
			printf("->%d", i);
		}
		putchar('\n');
	}
}
