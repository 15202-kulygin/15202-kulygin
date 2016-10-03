#include "input.h"

int inputcheck(int argc, char ** argv) /* проверяем, указан ли входной файл */
{
	if ((argc == 1) || (NULL == argv[1]))
	{
		return 0;
	}
	return 1;
}
int filecheck(int argc, char ** argv, FILE* input_file) /* проверяем входной файл на возможность открыть, 1 - все в порядке, иначе 0 */
{
	return (NULL != input_file);
}
int islaststring(char * string) /* проверяет, является ли строка последней */
{
	if (strlen(string) == 0)
		return 1;
	return 0;
}
int checkstring(char * string) /* проверяет строку на валидность */
{
	int i = 0;
	int spacect = 0;
	int pointct = 0;
	if (MAXSTRLEN < strlen(string))
		return 0;
	for (i = 0; i < strlen(string) - 1; ++i)
	{
		if ((!isalpha(string[i])) && (!isdigit(string[i])) && (string[i] != ' ') && (string[i] != '.'))
			return 0;
		if (string[i] == ' ')
			spacect++;
		if (string[i] == '.')
			pointct++;
	}
	if (2 != spacect)
		return 0;
	if (2 < pointct)
		return 0;
	i = 0;
	while (string[i] != ' ')
	{
		if (!isalpha(string[i]))
			return 0;
		++i;
	}
	++i;
	if (!isdigit(string[i]))
		return 0;
	while (string[i] != ' ')
	{
		if (!isdigit(string[i]) && (string[i] != '.'))
			return 0;
		++i;
	}
	++i;
	if (!isdigit(string[i]))
		return 0;
	while (i < strlen(string) - 1)
	{
		if (!isdigit(string[i]) && (string[i] != '.'))
			return 0;
		++i;
	}
	return 1;
}
char ** strings(FILE * input_file) /* считываем из файла строки и записываем их в массив строк */
{
	char ** str = (char **)calloc(1, sizeof(char *));
	str[0] = (char *)calloc(MAXSTRLEN, sizeof(char));
	fgets(str[0], MAXSTRLEN, input_file);
	if (strlen(str[0]) == 0) 
		return NULL;
	// if (0 == checkstring(str[0])
	//	return NULL;
	int i = 1;
	while (1)
	{
		str = (char **)realloc(str, (i + 1)*sizeof(char *));
		str[i] = (char *)calloc(MAXSTRLEN, sizeof(char));
		fgets(str[i], MAXSTRLEN, input_file);
		if (1 == islaststring(str[i]))
		{
			str[i] = NULL;
			free(str[i]);
			break;
		}
		/*if (0 == checkstring(str[i]))
		{
			return NULL;
		}*/
		i++;
	}
	return str;
}
int stringscount(char ** strings) /* считает количество строк в массиве строк */
{
	int i = 0;
	while (strings[i] != NULL)
		++i;
	return i;
}