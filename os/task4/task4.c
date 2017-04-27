#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
	char * str;
	struct List * next;
} List;

void add_node(List * head, char * new_str)
{
	if (NULL == head->str)
	{
		head->str = (char *) calloc (10, sizeof(char));
		strncpy(head->str, new_str, 10);
	}
	else
	{
		List * new_node = (List *) calloc (1, sizeof(List));
		new_node->str = (char *) calloc (10, sizeof(char));
		strncpy(new_node->str, new_str, 10);
		new_node->next = NULL;
		while (head->next != NULL)
		{
			head = head->next;
		}
		head->next = new_node;
	}
}

void print_list(List * head)
{
	while (NULL != head)
	{

		printf("%s", head->str);
		if ((10 == strlen(head->str)) && ('\n' != head->str[9]))
		{
			printf("\n");
		}
		//puts(head->str);
		head = head->next;
	}
}

void delete_list(List * head)
{
	if (NULL == head)
	{
		return;
	}
	if (NULL == head->next)
	{
		free(head->str);
		free(head);
		return;
	}
	List * temp;
	while (NULL != head->next)
	{
		temp = head->next;
		free(head->str);
		free(head);
		head = temp;
	}
}

int main()
{
	char * str = (char *) calloc (100, sizeof(char));
	List * head = (List *) calloc (1, sizeof(List));
	head->str = NULL;
	head->next = NULL;
	while (1)
	{
		fgets(str, 100, stdin);
		if ('.' == str[0])
		{
			add_node(head, str);
			printf("Printing the list:\n\n");
			print_list(head);
			delete_list(head);
			free(str);
			return 0;
		}
		else
		{
			add_node(head, str);
		}
	}
}