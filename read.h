#ifndef _READ_H
#define _READ_H

#include <stdio.h>
#include <string.h>

#include "structure.h"

char readChar(sysStatus * pstatus, int i);

void read(sysStatus * pstatus, char * cmdstr);

#endif
