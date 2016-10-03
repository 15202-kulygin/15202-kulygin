#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

char * getsequence(int * len, FILE * input_file)
{
	char c = ' ';
	char * seq = (char *) calloc (1, sizeof(char));
	while (1)
	{
		c = fgetc(input_file);
		if (('\n' == c) || (EOF == c))
			break;
		if (('a' != c) && ('A' != c) && ('t' != c) && ('T' != c) && ('g' != c) && ('G' != c) && ('c' != c) && ('C' != c) && ('u' != c) && ('U' != c))
		{
			free(seq);
			return NULL;
		}
		seq = (char *) realloc (seq, (*len+1)*sizeof(char));
		seq[*len] = (char)((int)c - (int)('a') + (int)('A'));
		(*len)++;
	}
	seq = (char *) realloc (seq, (*len+1)*sizeof(char));
	seq[*len] = '\0';
	return seq;
}