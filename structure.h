#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const char True = 1;
const char False = 0;
const int diskSize = 2 * 1024 * 1024;
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
	int strlen;			// (char *) malloc(pstatus->fcbs[newfcbid].strlen+2);
	boolean flagFoder;
	time_t create;
	time_t lastChange;
	int size;
	int nextIB;
}FCB;

const int fcbNum = 448;
const int ibNum = 4096-64;
typedef struct sysStatus
{
	char * disk = NULL;
	FCB fcbs[fcbNum];
	IB ibs[ibNum];
	int free_fcb;
	int free_ib;
	int full_fcb;
	int pwd;
}sysStatus;

void freeFCB(sysStatus * pstatus, int x);

void initFCB(sysStatus* pstatus, int x, boolean flagFoder);

int checkExist(sysStatus * pstatus, char * name);

void writeFCB(sysStatus * pstatus, int fcbid);

void readFCB(sysStatus * pstatus, int fcbid, FCB * dest);

void printFCB(FCB buf);

void writeIBp(sysStatus* pstatus, int id, int next);

#endif

