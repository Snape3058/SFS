#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include <time.h>

typedef char boolean;

typedef struct IB
{
	int nextIB;
	int contentBlockID;
}IB;

typedef struct FCB
{
	int nextFCB;
	int subFCB;
	char * filename;
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
}sysStatus;

#endif
