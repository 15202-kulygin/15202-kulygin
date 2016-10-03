#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "align.h"

int main(int argc, char ** argv)
{
	FILE * input_file = fopen(argv[1], "r");
	if (NULL == input_file)
	{
		printf("Can't open input file\n");
		return -1;
	}
	int len1 = 0;
	int len2 = 0;
	char * sequence1 = getsequence(&len1, input_file);
	char * sequence2 = getsequence(&len2, input_file);
	if ((NULL == sequence1) || (NULL == sequence2))
	{
		printf("Wrong file format\n");
		free(sequence1);
		free(sequence2);
		return -1;
	}
	printf("Sequencies reading completed\n");
	int ** matrix = (int **) calloc (len1 + 1, sizeof(int *));
	int ** trace = (int **) calloc (len1 + 1, sizeof(int *));
	int i = 0; 
	for (i = 0; i < len1 + 1; ++i)
	{
		matrix[i] = (int *) calloc (len2 + 1, sizeof(int));
		trace[i] = (int *) calloc (len2 + 1, sizeof(int));
	}
	fillmatrix(matrix, sequence1, sequence2, len1, len2, trace);
	printmatrix(matrix, len1, len2);
	traceback(matrix, sequence1, sequence2, len1, len2, trace);
	for (i = 0; i < len1 + 1; ++i)
	{
		free(matrix[i]);
		free(trace[i]);
	}
	free(matrix);
	free(trace);
	free(sequence1);
	free(sequence2);
	return 0;
}