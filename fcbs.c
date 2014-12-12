#include "fcbs.h"

void fcbs(sysStatus * pstatus)
{
	int i;
	char * c, * l;
	printf("free_fcb\t:%d\n", pstatus->free_fcb);
	printf("full_fcb\t:%d\n", pstatus->full_fcb);
	printf("ID\t|dadFCB\t|nextFCB|subFCB\t|Folder\t|create date\t\t\t|last change\t\t\t|size\t|nextIB\t|file name\n");
	printf("--------|-------|-------|-------|-------|-------------------------------|-------------------------------|-------|-------|--------\n");
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
