#ifndef _INC_19_UTIL_H_
#define _INC_19_UTIL_H_

#include <stdlib.h>

void * checkMalloc(size_t size);
int extendStr(char **str, size_t *length);
int addChar(char **str, size_t *length, size_t *pos, char c);

#endif //_INC_19_UTIL_H_

