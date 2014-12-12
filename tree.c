#include "tree.h"

void tree(sysStatus * pstatus, int pwd, int level)
{
	int i, p;
	for ( p = pstatus->fcbs[pwd].subFCB; p != -1; p = pstatus->fcbs[p].nextFCB )
	{
		for ( i = 0; i < level; i ++ )
		{
			printf("  ");
		}
		printf("|-%s\n", pstatus->fcbs[p].filename);
		tree(pstatus, p, level+1);
	}
	return ;
}
