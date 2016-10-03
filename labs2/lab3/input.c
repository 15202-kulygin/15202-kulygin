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
	arr[0] = (link *) calloc (1, sizeof(link));
	int a = -1;
	int b = -1;
	int capacity = -1;
	++i;
	int rc = fscanf (input_file, "%d %d %d", &a, &b, &capacity);
	while (3 == rc)
    {
    	arr = (link **) realloc (arr, i*2*sizeof(link *));
    	arr[i] = (link *) calloc (1, sizeof(link));    	
    	arr[i]->a = a;
    	arr[i]->b = b;
    	arr[i]->capacity = capacity;
    	i++;
		rc = fscanf (input_file, "%d %d %d", &a, &b, &capacity);    
	}
    arr[0]->a = i;
    arr[0]->b = i;
    arr[0]->capacity = i;
    return arr;
}