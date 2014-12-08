#ifndef _NEW_H
#define _NEW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"

const int diskSize = 2 * 1024 * 1024;

void New(
	char * filename, 
	char * cmdstr, 
	char * pwd, 
	char ** disk,
	sysStatus * pstatus
);

#endif
