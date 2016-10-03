#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "graph.h"

int main (int argc, char ** argv)
{
	if (0 == inputcheck(argc, argv))
    {
    	printf ("Put in the name as the first argument after the progrun command\n");
       	return -1;
    }
    FILE* input_file = fopen (argv[1], "r");
    if (0 == filecheck(argc, argv, input_file))
    {
    	printf ("Can't open input file\n");
    	return -1;
    }
    link ** links = makelinks(input_file);
    if (NULL == links)
    {
    	fclose(input_file);
    	return -1;
    }
    if (links[0]->a == -1)
    {
    	int i = 0;
    	printf("Input file is empty\n");
    	fclose(input_file);
    	for (i = 0; links[i] != NULL; ++i)
    	{
    		free(links[i]);
    		links[i] = NULL;
    	}
    	free(links);
    	links = NULL;
    	return -1;
    }
    int size = SIZE;
    graph ** vertexes = (graph **) calloc (size, sizeof(graph *));
    int count = 0; /* current quantity of vertexes */
    int i = 0;
    int j = 0;
    for (i = 0; links[i] != NULL; ++i)
    	addlink(links[i], vertexes, &count, &size);
    for (i = 0; links[i] != NULL; ++i)
    {
    	free(links[i]);
    	links[i] = NULL;
    }
    free(links);
    for (i = 0; i < size; ++i)
    {
        if (NULL != vertexes[i])
        {
            graph * start = vertexes[i];
            while (NULL != start)
            {
                printf ("%d id vertex, connected with : ", start->id);
                for (j = 0; j < start->ct; ++j)
                    printf("%d id ", start->arr[j]->id);
                printf("\n");
                start = start->next;
            }
        }
    }
    /*for (i = 0; i < count; ++i)
    {
    	printf ("%d-th vertex. id %d. connected with: ", i+1, vertexes[i]->id);
    	for (j = 0; j < vertexes[i]->ct; ++j)
    		printf ("%d-th vertex ", vertexes[i]->arr[j]->id);
    	printf("\n");
    }
    width(vertexes[0]);*/
    return 0;
}