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
    if (links[0]->a == 1)
    {
    	int i = 0;
    	printf("Input file is empty\n");
    	fclose(input_file);
    	free(links[0]);
    	free(links);
    	return -1;
    }
    int linksct = links[0]->a;
    free(links[0]);
    int i = 0;
    int size = 2;
    graph ** vertexes = (graph **) calloc (size, sizeof(graph *));
    int count = 0; /* current quantity of vertexes */
    for (i = 1; i < linksct; i++)
    {
    	addlink(links[i], vertexes, &count, &size);
    	if ( ((float)count / (float)size) >= LOADFACTOR )
    		vertexes = remake(&vertexes, links, count, &size);
    }
    for (i = 1; i < linksct; ++i)
    	free(links[i]);
    free(links);
    printgraph (vertexes, size);
    int startid1 = 0;
    int startid2 = 0;
    printf("Print the ids of the vertexes to count maximal flow:\n");
    scanf("%d %d", &startid1, &startid2);
    graph * search1 = searchvert(vertexes, startid1, size);
    graph * search2 = searchvert(vertexes, startid2, size);
    int result = find_max_flow(search1, search2, vertexes, size);
    printgraph (vertexes, size);
    printf("Max flow value : %d\n", result);
    deletegraph(vertexes, size);
    free(vertexes);
    return 0;
}