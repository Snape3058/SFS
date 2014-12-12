#include "ls.h"

void ls(sysStatus * pstatus)
{
	int i;
	char * c, * l;
	if ( ~ pstatus->fcbs[pstatus->pwd].subFCB )
	{
		printf("size\t|create date\t\t\t|last change\t\t\t|file name\n");
		printf("--------|-------------------------------|-------------------------------|----------\n");
		for ( i = pstatus->fcbs[pstatus->pwd].subFCB; i != -1; i = pstatus->fcbs[i].nextFCB )
		{
			c = ctime(&(pstatus->fcbs[i].create));
			c[strlen(c)-1] = 0;
			l = ctime(&(pstatus->fcbs[i].lastChange));
			l[strlen(l)-1] = 0;
			printf("%d\t|%s\t|%s\t|", pstatus->fcbs[i].size, c, l);
			if ( pstatus->fcbs[i].flagFoder )
			{
				printf("\033[34m");
			}
			printf("%s\033[0m\n", pstatus->fcbs[i].filename);
		}
	}
	else
	{
		printf(">>> NULL!\n");
	}
}
