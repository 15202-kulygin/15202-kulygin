#if!defined (ALIGN_H)
#define ALIGN_H

#include <stdio.h>

#define MATCH 5
#define DISMATCH -4
#define OPEN_GAP -10
#define EXT_GAP -1
#define UP 1
#define LEFT -1
#define DIAG 0

void fillmatrix(int ** matrix, char * sequence1, char * sequence2, int len1, int len2, int ** trace);
int maxof3(int a, int b, int c);
void printmatrix(int ** matrix, int len1, int len2);
void deletematrix(int ** matrix, int len1, int len2);
void traceback(int ** matrix, char * sequence1, char * sequence2, int len1, int len2, int ** trace);
char * reverse(char * str, int len);
#endif