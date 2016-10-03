#include "input.h"
#include "hash.h"
#include "graph.h"


#if !defined(P)
#define P 7
#endif

char ** makekeys (char ** strings, int strct) /* делает массив строковых ключей (фамилий студентов) из массива строк */
{
	char ** k = (char **) calloc (strct, sizeof(char*));
	int i = 0;
	int j = 0;
	for (i = 0; i < strct; ++i)
	{
		k[i] = (char *) calloc (MAXNAME, sizeof(char));
		j = 0;
		while (strings[i][j] != ' ')
		{
			k[i][j] = strings[i][j];
			++j;
		}
		k[i][j] = '\0';
		if (strlen(k[i]) > MAXNAME)
		{
			free (k[i]);
			free (k);
			return NULL;
		}
	}
	return k;
}
ht ** maketables (char ** strings, int strct) /* делает массив одноэлементных списков (каждый элемент - звено списка с ростом
и весом студента) из массива строк */
{
	ht ** t = (ht **) calloc (strct, sizeof(ht*));
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < strct; ++i)
	{
		t[i] = (ht *) calloc (1, sizeof(ht));
		j = 0;
		t[i]->name = (char *) calloc (MAXNAME, sizeof(char));
		while (strings[i][j] != ' ')
		{
			t[i]->name[j] = strings[i][j];
			++j;
		}
		t[i]->name[j] = '\0';
		if (strlen(t[i]->name) > MAXNAME)
		{
			free (t[i]->name);
			free (t[i]);
			return NULL;
		}
		j++;
		char * h = (char *) calloc (MAXHEIGHT, sizeof(char));
		k = 0;
		while (strings[i][j] != ' ')
		{
			h[k] = strings[i][j];
			++k;
			++j;
		}
		h[k] = '\0';
		if (strlen(h) > MAXHEIGHT)
		{
			free(h);
			free(t[i]);
			free(t);
			return NULL;
		}
		t[i]->height = atof(h);
		free(h);
		++j;
		k = 0;
		char * w = (char *) calloc (MAXHEIGHT, sizeof(char));
		if (i == strct - 1)
		{
			while (j < strlen(strings[i]))
			{
				w[k] = strings[i][j];
				++k;
				++j;
			}
		}
		else
		{
			while (j < strlen(strings[i]) - 1)
			{
				w[k] = strings[i][j];
				++k;
				++j;
			}
		}
		w[k] = '\0';
		if (strlen(w) > MAXHEIGHT)
		{
			free(w);
			free(t[i]);
			free(t);
			return NULL;
		}
		t[i]->weight = atof(w);
		free(w);
		free(strings[i]);
	}
	return t;
} 
ht ** makeht (long long int size) /* делает хэш-таблицу заданного размера */
{
	ht ** htable = (ht **) calloc (size, sizeof(ht*));
	return htable;
}
int hash (int key, long long int size) /* хэш-функция */
{
	long long int h = 0;
	int p = 1;
	while (0 != key)
	{
		h += (key%10)*p;
		p *= P;
		key /= 10;
	}
	return (int)((h)%size);
}
void add (ht ** hashtable, long long int size, char * key, ht * table) /* добавляет в хэш-таблицу запись по ключу */
{
	int h = hash(key, size);
	ht * check = hashtable[h];
	if (NULL != check)
	{
		while (NULL != check)
		{
			if (strcmp(key, check->name) == 0)
				return;
			check = check->next;
		}
	}
	if (NULL == hashtable[h])
	{
		hashtable[h] = table;
	}
	else
	{
		ht * start = hashtable[h];
		while (NULL != start->next)
			start = start->next;
		start->next = table;
	}
}
ht ** remake (ht ** hashtable, long long int * size, char ** keys, ht ** tables, int strct) /* переcтраивает таблицу */
{
	int j = 0;
	for (j = 0; j < *size; ++j)
		hashtable[j] = NULL;
	free(hashtable);
	*size = *size * 2;
	ht ** newht = (ht **) calloc (*size, sizeof(ht *));
	for (j = 0; j < strct; ++j)
	{
		add(newht, *size, keys[j], tables[j]);
	}
	printf("Table remade.\n\n");
	return newht;
}
int searchclear (char * key, ht ** hashtable, long long int size) /* поиск записи по ключу без вывода информации*/
{
	int h = hash(key, size);
	ht * start = hashtable[h];
	while (NULL != hashtable[h])
	{
		if (strcmp(hashtable[h]->name, key) == 0)
		{
			return 1;
		}
		hashtable[h] = hashtable[h]->next;
	}
	hashtable[h] = start;
	return 0;	
}
void delete (char * key, ht ** hashtable, long long int size) /* удаление записи по ключу */
{
	int h = hash(key, size);
	if (NULL == hashtable[h])
	{
		return;
	}
	if (strcmp(hashtable[h]->name, key) == 0)
	{
		ht * temp = hashtable[h]->next;
		free(hashtable[h]);
		hashtable[h] = temp;
		return;
	}
	ht * start = hashtable[h]->next;
	ht * prev = hashtable[h];
	while (NULL != start)
	{
		if (strcmp(start->name, key) == 0)
		{
			prev->next = start->next;
			free(start); 
			return;
		}
		prev = start;
		start = start->next;
	}
	return;
}
void printtable(ht * table) /* печатает все записи данного списка таблицы */
{
	if (NULL == table)
 		return;
 	printf("%s %.1f %.2f\n", table->name, table->height, table->weight);
	if (NULL != table->next)
	{	
		printtable(table->next);
		return;
	}
	return;
}
void printht (ht ** hashtable, long long int size) /* печатает данную таблицу данного размера */
{
	int i = 0;
	printf("\n");
	for (i = 0; i < size; ++i)
    {
        if (NULL != hashtable[i])
        {
            printf("%d-th note:\n", i+1);
            printtable(hashtable[i]);
        }
    }
    printf("\n");
}
void deleteht (ht ** hashtable, long long int size) /* удаляет таблицу */
{
	long long int i = 0;
	for (i = 0; i < size; ++i)
	{
		if (NULL != hashtable[i])
		{
			ht * p = hashtable[i];
			while (NULL != hashtable[i]->next)
			{
				p = hashtable[i]->next;
				free(hashtable[i]);
				hashtable[i] = p;
			}
		}
	}
	printf("Table deleted.\n");
}