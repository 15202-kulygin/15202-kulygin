#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "align.h"

int maxof3(int a, int b, int c)
{
	int win1;
	if (a >= b)
		win1 = a;
	else
		win1 = b;
	int win2;
	if (win1 >= c)
		win2 = win1;
	else
		win2 = c;
	return win2;
}
void fillmatrix(int ** matrix, char * sequence1, char * sequence2, int len1, int len2, int ** trace)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < len1 + 1; ++i)
	{
		for (j = 0; j < len2 + 1; ++j)
		{
			if ((0 == i) && (0 == j))
			{
				matrix[i][j] = 0;
				trace[i][j] = 0;
				continue;
			}
			else if (0 == i)
			{
				/*if (1 == j)
					matrix[i][j] = matrix[i][j-1] + OPEN_GAP;
				else
					matrix[i][j] = matrix[i][j-1] + EXT_GAP;*/
				matrix[i][j] = 0;
				trace[i][j] = UP;
				continue;
			}
			else if (0 == j)
			{
				/*if (1 == i)
					matrix[i][j] = matrix[i-1][j] + OPEN_GAP;
				else
					matrix[i][j] = matrix[i-1][j] + EXT_GAP;*/
				matrix[i][j] = 0;
				trace[i][j] = LEFT;
				continue;
			}
			else
			{
				int top = 0;
				int left = 0;
				if (trace[i][j-1] == UP)
				{
					top = matrix[i][j-1] + EXT_GAP;
				}
				else
					top = matrix[i][j-1] + OPEN_GAP;	
				if (trace[i-1][j] == LEFT)
				{
					left = matrix[i-1][j] + EXT_GAP;
				}
				else
					left = matrix[i-1][j] + OPEN_GAP;
				int ismatch = 0;
				if (sequence1[i-1] == sequence2[j-1])
				{
					ismatch = MATCH;
				}
				else
					ismatch = DISMATCH;
				int diag = matrix[i-1][j-1] + ismatch;
				int result = maxof3(top, left, diag);
				matrix[i][j] = result;
				if (result == diag)
					trace[i][j] = DIAG;
				else if (result == top)
					trace[i][j] = UP;
				else if (result == left)
					trace[i][j] = LEFT;
			}
		}
	}
}
void printmatrix(int ** matrix, int len1, int len2)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < len1 + 1; ++i)
	{
		for (j = 0; j < len2 + 1; ++j)
		{
			printf("%2d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void traceback(int ** matrix, char * sequence1, char * sequence2, int len1, int len2, int ** trace)
{
	int matches = 0;
	int i = len1;
	int j = len2;
	int reslen = 0;
	char * result1 = (char *) calloc (1, sizeof(char));
	char * result2 = (char *) calloc (1, sizeof(char));
	while (1)
	{
		//printf("%d %d check\n", i, j);
		result1 = (char *) realloc(result1, (reslen + 1)*sizeof(char));
		result2 = (char *) realloc(result2, (reslen + 1)*sizeof(char));
		if ((0 == i) && (0 == j))
		{
			printf("\n\nAligned:\n\n");
			int k = 0;
			for (k = 0; k < reslen; ++k)
				printf("%c", result1[reslen - k - 1]);
			printf("\n");
			for (k = 0; k < reslen; ++k)
			{
				if (result1[reslen - k - 1] == result2[reslen - k - 1])
				{
					printf("|");
					matches++;
				}
				else
					printf(" ");
			}
			printf("\n");
			for (k = 0; k < reslen; ++k)
				printf("%c", result2[reslen - k - 1]);
			printf("\n\n");
			printf("Matches : %d\n", matches);
			printf("Score : %d\n\n", matrix[len1][len2]);
			free(result1);
			free(result2);
			return;
		}
		if (trace[i][j] == DIAG)
		{
			result1[reslen] = sequence1[i-1];
			result2[reslen] = sequence2[j-1];
			i--;
			j--;
		}
		else if (trace[i][j] == UP)
		{
			result1[reslen] = '-';
			result2[reslen] = sequence2[j-1];
			j--;
		}
		else if (trace[i][j] == LEFT)
		{
			result1[reslen] = sequence1[i-1];
			result2[reslen] = '-';
			i--;
		}
		reslen++;
	}
}
char * reverse(char * str, int len)
{
	int i = 0;
	char * result = (char *) calloc (len, sizeof(char));
	for (i = 0 ; i < len; ++i)
		result[i] = str[len - i - 1];
	free(str);
	return result;
}