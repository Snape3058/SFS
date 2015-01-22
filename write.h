#ifndef _WRITE_H
#define _WRITE_H

#include <stdio.h>
#include <string.h>

#include "structure.h"

void writeChar(sysStatus * pstatus, int i, char ch);
void write(sysStatus * pstatus, char * cmdstr);

#endif
