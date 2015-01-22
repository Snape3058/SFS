#ifndef _OPEN_CLOSE_H
#define _OPEN_CLOSE_H

#include <stdio.h>
#include <string.h>

#include "structure.h"

void open(sysStatus * pstatus, char * cmdstr, char * pwd);
void close(sysStatus * pstatus, char * cmdstr, char * pwd);

#endif
