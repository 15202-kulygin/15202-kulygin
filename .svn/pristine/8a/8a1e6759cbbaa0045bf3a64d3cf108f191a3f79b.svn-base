#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "hash.h"

int main(int argc, char ** argv)
{

	if (0 == inputcheck(argc, argv))
	{
		printf("Put in the name as the first argument after the progrun command\n");
		return -1;
	}
	FILE* input_file = fopen(argv[1], "r");
	if (0 == filecheck(argc, argv, input_file))
	{
		printf("Can't open input file\n");
		return -1;
	}
	long long int i = 0;
	char ** s = strings(input_file);
	fclose(input_file);
	if (NULL == s)
	{
		printf("Wrong strings format; print them like 'Petrov 170 66.6', using only\n");
		printf("English letters, digits, spaces and points\n");
		free(s);
		return -1;
	}
	long long int strct = stringscount(s);
	char ** keys = makekeys(s, strct);
	if (NULL == keys)
	{
		printf("Too long name string, it should be less than 21 sym\n");
		free(keys);
		free(s);
		return -1;
	}
	ht ** tables = maketables(s, strct);
	if (NULL == tables)
	{
		printf("Too long height or weight string, it should be less than 7 sym\n");
		free(keys);
		free(tables);
		free(s);
		return -1;
	}
	long long int size = M;
	ht ** hashtable = makeht(size);
	float filled = 0;
	float factor = 0;
	char ** tempkeys = (char **)calloc(1, sizeof(char *));
	ht ** temptables = (ht **)calloc(1, sizeof(ht *));
	long long int k = 0;
	i = 0;
	printf("Creating hashtable.\n");
	printf("%d size\n", strct);
	while (i < strct)
	{
		add(hashtable, size, keys[i], tables[i]);
		i++;
		filled++;
		factor = filled / size;
		while (factor >= LOADFACTOR)
		{
			tempkeys = (char **)realloc(tempkeys, i * sizeof(char *));
			temptables = (ht **)realloc(temptables, i * sizeof(ht *));
			for (k = 0; k < i; ++k)
			{
				tempkeys[k] = keys[k];
				temptables[k] = tables[k];
			}
			hashtable = remake(hashtable, &size, tempkeys, temptables, i);
			factor = filled/size;
		}
	}
	printf("Hashtable made:\n");
	//printht(hashtable, size);
	printf("Search mode began. Print -end to end.\n");
	while (1)
	{
		char * get = (char *)calloc(MAXNAME, sizeof(char));
		scanf("%s", get);
		if (strcmp(get, "-end") == 0)
		{
			deleteht(hashtable, size);
			return -1;
		}
		search(get, hashtable, size);
		free(get);
		get = NULL;
	}
	free(s);
	return 0;
}