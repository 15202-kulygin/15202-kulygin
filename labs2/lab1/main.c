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
    /*if (NULL == links)
    {
        int count = links[0]->a;
        int k = 0;
        for (k = 0; k < l)
    	fclose(input_file);
    	return -1;
    }*/
    if (links[0]->a == -1)
    {
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
    int startid = 0;
    printf("Print the index of the vertex to begin from:\n");
    scanf("%d", &startid);
    graph * search = searchvert(vertexes, startid, size);
    if (NULL == search)
    {
    	printf("Wrong id : no such vertex in the graph\n");
    }
    else
    {
        width(search);  
    }
    deletegraph(vertexes, size);
    free(vertexes);   
    return 0;
}