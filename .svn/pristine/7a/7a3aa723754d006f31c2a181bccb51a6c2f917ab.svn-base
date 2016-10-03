#include "input.h"
#include "list.h"
#include "tree.h"


list * splitstring (char * str, int strn, int strct) /* делит строку на имя, рост и вес, возвращает указатель на звено списка, состоящего
из этой информации */
{
	list * listik = (list*) calloc (1, sizeof(list));
	int i = 0;
	int j = 0;
	listik->name = (char*) calloc (MAXNAME, sizeof(char));
	while (str[i] != ' ')
	{
		listik->name[i] = str[i];
		i++;
	}
	listik->name[i] = '\0';
	if (strlen(listik->name) > MAXNAME)
	{
		free (listik->name);
		free (listik);
		return NULL;
	}
	i++;
	char * h = (char *) calloc (MAXHEIGHT, sizeof(char));
	while (str[i] != ' ')
	{
		h[j] = str[i];
		i++;
		j++;
	}
	h[j] = '\0';
	if (strlen(h) > MAXHEIGHT)
	{
		free (listik->name);
		free (listik);
		free (h);
		return NULL;
	}	
	listik->height = atof(h);
	free (h);
	i++;
	j = 0;
	char * w = (char *) calloc (MAXHEIGHT, sizeof(char));
	if (strn == strct -1)
	{
		while (i < strlen(str))
		{
			w[j] = str[i];
			i++;
			j++;
		}
	}
	else
	{
		while (i < strlen(str) - 1)
		{
			w[j] = str[i];
			i++;
			j++;
		}
	}
	w[j] = '\0';
	if (strlen(w) > MAXHEIGHT)
	{
		free (listik->name);
		free (listik);
		free (w);
		return NULL;
	}
	listik->weight = (float) atof(w);
	free (w);
	free (str);
	return listik;
}
list * makelist (char ** strings, int strct) /* делает список из массива строк */
{
	int i = 0;
	list * head = splitstring (strings[0], 0, strct);
	if (NULL == head)
	{
		free (strings);
		return NULL;
	}
	list * cur = head;
	list * nex = NULL;
	while (i < strct - 1)
	{
		nex = splitstring(strings[i+1], i+1, strct);
		if (NULL == nex)
		{
			free (strings);
			return NULL;
		}
		cur->next = nex;
		cur = nex;
		++i;
	}
	cur->next = NULL;
	return head;
}
void sortlist (list * head) /* сортирует список по возрастанию имен */
{
	list * start = head;
	list * p = NULL;
	int i = 0;
	while (head->next != NULL)
	{
		p = head->next;
		printf("%d i\n", i);
		do 
		{
			if (strcmp(p->name, head->name) < 0)
			{
				char * temp = head->name;
				head->name = p->name;
				p->name = temp;
				swapf (&head->height, &p->height);
				swapf (&head->weight, &p->weight);
			}
			p = p->next;
		} while (p != NULL);
	head = head->next;
	++i;
	}
	head = start;
}
void deletelist (list * head) /* удаляет список */
{
	if (NULL != head)
	{
		deletelist(head->next);
		free (head);
	}
}