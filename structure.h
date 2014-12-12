#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include <time.h>
#include <string.h>

const char True = 1;
const char False = 0;
typedef char boolean;

typedef struct IB
{
	int nextIB;
	int contentBlockID;
}IB;

typedef struct FCB
{
	int dadFCB;
	int nextFCB;
	int subFCB;
	char * filename;
	int strlen;
	boolean flagFoder;
	time_t create;
	time_t lastChange;
	int size;
	int nextIB;
}FCB;

const int fcbNum = 448;

typedef struct sysStatus
{
	FCB fcbs[fcbNum];
	IB ibs[4096];
	int free_fcb;
	int free_ib;
	int full_fcb;
	int pwd;
}sysStatus;

void initFCB(sysStatus* pstatus, int x, boolean flagFoder);

int checkExist(sysStatus * pstatus, char * name);

#endif

