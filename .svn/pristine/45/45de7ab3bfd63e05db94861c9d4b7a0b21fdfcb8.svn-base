#include "input.h"

int inputcheck(int argc, char ** argv) /* check if filename was put in */
{
	if ((argc == 1) || (NULL == argv[1]))
	{
		return 0;
	}
	return 1;
}
int filecheck(int argc, char ** argv, FILE* input_file) /* check if it's possible to open input file */
{
	return (NULL != input_file);
}
link ** makelinks(FILE * input_file) /* check if the strings are correct and make an array */
{
	link ** arr = (link **) calloc (1, sizeof(link *));
	int i = 0;
	int a = -1;
	int b = -1;
	while (!feof(input_file))
    {
    	arr = (link **) realloc (arr, (i+1)*sizeof(link *));
    	arr[i] = (link *) calloc (1, sizeof(link));
    	int rc = fscanf (input_file, "%d %d", &a, &b);
		if (2 != rc)
		{
			printf("%d-th line : wrong format\n", i+1);
			return NULL;
		}    	
    	arr[i]->a = a;
    	arr[i]->b = b;
    	i++;
    }
    arr[i] = NULL;
    return arr;
}