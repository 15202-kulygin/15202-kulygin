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
	int a1 = -1;
	int a2 = -1;
	int b1 = -1;
	int b2 = -1;
	int weight = -1;
	++i;
	int rc = fscanf (input_file, "%d %d %d %d %d", &a1, &a2, &b1, &b2, &weight);
	while (5 == rc)
    {
    	arr = (link **) realloc (arr, i*2*sizeof(link *));
    	arr[i] = (link *) calloc (1, sizeof(link));    	
    	arr[i]->a1 = a1;
    	arr[i]->a2 = a2;
    	arr[i]->b1 = b1;
    	arr[i]->b2 = b2;
    	arr[i]->weight = weight;
    	i++;
    	rc = fscanf (input_file, "%d %d %d %d %d", &a1, &a2, &b1, &b2, &weight);
    }
    arr[0]->a1 = i;
    arr[0]->a2 = i;
    arr[0]->b1 = i;
    arr[0]->b2 = i;
    arr[0]->weight = i;
    return arr;
}