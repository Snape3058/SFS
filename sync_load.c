#include "sync_load.h"

void sync(sysStatus * pstatus, char * filename)
{
	FILE * fp = fopen(filename, "wb");
	if ( ! fp )
	{
		printf("\033[31m>>> Error while opening the file!\033[0m\n");
		return ;
	}
	if ( diskSize != fwrite(pstatus->disk, 1, diskSize, fp) )
	{
		printf("\033[31m>>> Error while writing to the file!\033[0m\n");
		return ;
	}
	else
	{
		printf("\033[32m>>> Synced!\033[0m\n");
		return ;
	}
}

void load(sysStatus * pstatus, char * cmdstr, char * filename, char * pwd)
{
	FILE * fp = NULL;
	int i;
	if ( pstatus->disk )
	{
		printf("\033[31m>>> An SFS has already been opened!\033[0m\n");
		return ;
	}
	if ( '\0' == cmdstr[0] || '\n' == cmdstr[0] )
	{
		printf(">>> sfs [filename]\n"
			">>> Please enter the name of the restore file.\n");
		return ;
	}
	else
	{
		sscanf(cmdstr, "%s", filename);
		printf(">>> SFS loading from: %s\n", filename);
	}
	pstatus->disk = (char *) malloc (diskSize);
	if ( NULL == pstatus->disk )
	{
		printf("\033[31m>>> malloc failed!\033[0m\n");
		return ;
	}
	memset(pstatus->disk, 0, diskSize);
	fp = fopen(filename, "rb");
	if ( ! fp )
	{
		printf("\033[31m>>> Error while opening the file!\033[0m\n");
		return ;
	}
	i = fread(pstatus->disk, 1, diskSize, fp);
	if ( diskSize != i )
	{
		printf("\033[31m>>> Error while loading from the file!\033[0m\n");
		free(pstatus->disk);
		pstatus->disk = NULL;
		sprintf(filename, "(NULL)");
		return ;
	}
	for ( i = 0; i < fcbNum; i ++ )
	{
		readFCB(pstatus, i, pstatus->fcbs+i);
	}
	for ( i = 0; i < ibNum; i ++ )
	{
		readIB(pstatus, i);	
		pstatus->ibs[i].contentBlockID = 512*(64+i) + sizeof(int);
	}
	readStatus(pstatus);
	printf("\033[32m>>> Loaded!\033[0m\n");
	sprintf(pwd, "/");
	return ;
}
