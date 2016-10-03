#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "graph.h"
#include "fibo.h"

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
    if (links[0]->a1 == 1)
    {
    	int i = 0;
    	printf("Input file is empty\n");
    	fclose(input_file);
    	free(links[0]);
    	free(links);
    	return -1;
    }
    int linksct = links[0]->a1;
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
    int startid1x = 0;
    int startid1y = 0;
    int startid2x = 0;
    int startid2y = 0;
    printf("Print the coordinates of the vertex to count minimal distance:\n");
    scanf("%d %d %d %d", &startid1x, &startid1y, &startid2x, &startid2y);
    graph * search1 = searchvert(vertexes, startid1x, startid1y, size);
    graph * search2 = searchvert(vertexes, startid2x, startid2y, size);
    if ((NULL == search1) || (NULL == search2))
    {
    	printf("Wrong coordinates : no such vertex in the graph\n");
    	deletegraph(vertexes, size);
    	free(vertexes);
    	return -1;
    }
    else
    {
        int result = distance(search1, search2);
        if (-1 != result)
            printf("The shortest way length (from %d %d to %d %d) is  :  %d\n", search1->x, search1->y, search2->x, search2->y, result);
        else
            printf("There is no way from %d %d to %d %d\n", search1->x, search1->y, search2->x, search2->y);
        deletegraph(vertexes, size);
        free(vertexes);
    }
    return 0;
}