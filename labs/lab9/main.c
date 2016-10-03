#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "list.h"
#include "tree.h"
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
    int i = 0;
    char ** s = strings(input_file);
    fclose(input_file);
    if (NULL == s)
    {
        printf ("Wrong strings format; print them like 'Petrov 170 66.6', using only\n");
        printf ("English letters, digits, spaces and points\n");
        free(s);
        return -1;
    }
    int strct = stringscount(s);
    list * head = makelist(s, strct);
	free (s);
    if (NULL == head)
    {
        printf ("Can't make a list : too long height or weight length, it should be less than 6 sym\n");
        free (head);
        return -1;
    }
    sortlist(head);
	printf(" ");
    tree * root = maketree(&head, strct);
    deletelist(head);
    while (1)
    {
        printf("Put in the student's name to search or '-end' to end:\n");
        char * getname = (char*) calloc (MAXNAME, sizeof(char));
        gets(getname);
        if (strcmp(getname, "-end") == 0)
        {
            deletetree(root);
            break;
        }
        if (0 == searchtree(root, getname))
            printf("The student wasn't found\n\n");
        free (getname);
    }
    return 0;
}