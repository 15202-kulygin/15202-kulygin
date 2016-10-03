#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
enum state {dead, alive};
static const char deadchar = '.';
static const char livingchar = '*';
int inputcheck (int argc, char ** argv) /* проверяем, указан ли входной файл */
{
	if ((argc == 1) || (NULL == argv[1])) 
	{
		return 0;
	}
	return 1;
}
int filecheck (int argc, char ** argv, FILE* input_file) /* проверяем входной файл на возможность открыть, 
1 - все в порядке, иначе 0 */
{
	return (NULL != input_file);
}
int * checkrules (FILE * input_file, int * rules) /* проверяем правильность введенных правил в файле, возвращает NULL, 
если все плохо, и массив с значениями рождения\выживания клеток иначе */
{
	char * r = calloc (50, sizeof(char));
	fgets (r, 50, input_file);
	if (25 < strlen(r))
	{
		free (r);
		return NULL;
	}
	int i = 0;
	int ct1 = 0;
	int ct2 = 0;
	int ct3 = 0;
	int ct4 = 0;
	int ct5 = 0;
	int ct6 = 0;
	for (i = 0; i < strlen(r) - 1; ++i)
	{
		if ((r[i]!='#')&&(r[i]!='R')&&(r[i]!=' ')&&(r[i]!='B')&&(r[i]!='/')&&(r[i]!='S')&&(!isdigit(r[i])))
			{ 
				free (r);
				return NULL;
			}
		if (r[i] == '9')
			{ 
				free (r);
				return NULL;
			}
		if (r[i] == '#')
			ct1++;
		if (r[i] == 'R')
			ct2++;
		if (r[i] == ' ')
			ct3++;
		if (r[i] == 'B')
			ct4++;
		if (r[i] == '/')
			ct5++;
		if (r[i] == 'S')
			ct6++;
	}
	if ((ct1 != 1)||(ct2 != 1)||(ct3 != 1)||(ct4 != 1)||(ct5 != 1)||(ct6 != 1))
	{ 
		free (r);
		return NULL;
	}
	if ((r[0] != '#') || (r[1] != 'R') || (r[2] != ' ') || (r[3] != 'B'))
	{ 
		free (r);
		return NULL;
	}

	i = 0;
	int j = 0;
	for (i = 0; i < 18; ++i)
		rules[i] = 0;
	i = 4;
	while (isdigit(r[i]))
	{
		rules[(int)(r[i]) - (int)('0')] = 1; 
		++i;
		++j;
	}
	if ((r[i] != '/') || (r[i+1] != 'S'))
	{ 
		free (r);
		return NULL;
	}
	i += 2;
	j = 9;
	while (isdigit(r[i]))
	{
		rules[(int)(r[i]) - (int)('0') + 9] = 1;
		++i;
		++j;
	}
	free (r);
	return rules;
}
int * checksize (FILE * input_file, int * size) /* проверяем размер */
{
	char * s = calloc (50, sizeof(char));
	fgets (s, 50, input_file);
	if (12 < strlen(s))
	{
		free (s);
		return NULL;
	}
	int i = 0;
	int ct1 = 0;
	int ct2 = 0;
	int ct3 = 0;
	int ct4 = 0;
	int ct5 = 0;
	int ct6 = 0;
	for (i = 0; i < strlen(s) - 1; ++i)
	{
		if ((s[i]!='#')&&(s[i]!='S')&&(s[i]!='i')&&(s[i]!='z')&&(s[i]!='e')&&(s[i]!=' ')&&(!isdigit(s[i])))
			{ 
				free (s);
				return NULL;
			}
		if (s[i] == '#')
			ct1++;
		if (s[i] == 'S')
			ct2++;
		if (s[i] == 'i')
			ct3++;
		if (s[i] == 'z')
			ct4++;
		if (s[i] == 'e')
			ct5++;
		if (s[i] == ' ')
			ct6++;
	}
	if ((ct1 != 1)||(ct2 != 1)||(ct3 != 1)||(ct4 != 1)||(ct5 != 1)||(ct6 != 2))
	{ 
		free (s);
		return NULL;
	}
	if ((s[0] != '#') || (s[1] != 'S') || (s[2] != 'i') || (s[3] != 'z') || (s[4] != 'e') || (s[5] != ' '))
	{ 
		free (s);
		return NULL;
	}
	for (i = 0; i < 2; ++i)
	{
		size[i] = 0;
	}
	int j = 0;
	i = 6;
	char first[3];
	char second[3];
	first[0] = 'x';
	first[1] = 'x';
	second[0] = 'x';
	second[1] = 'x';
	first[2] = '\0';
	second[2] = '\0';
	while (isdigit(s[i]))
	{
		first[j] = s[i];
		++i;
		++j;
	}
	++i;
	j = 0;
	while (isdigit(s[i]))
	{
		second[j] = s[i];
		++i;
		++j;
	}
	size[0] = atoi(first);
	size[1] = atoi(second);
	if ((3 > size[0]) || (50 < size[0]) || (3 > size[1]) || (50 < size[1]))
	{
		free (s);
		return NULL;
	}
	free (s);
	return size;
}
int livenup (int ** field, int height, int width, FILE * input_file)
{
	char * s = calloc (50, sizeof(char));
	int x = 0;
	int y = 0;
	int i = 0;
	int j = 0;
	int ct = 0;
	while (!feof(input_file))
	{
		fgets (s, 50, input_file);
		if ((strlen(s) < 3) || (strlen(s) > 6))
			return 0;
		ct = 0;
		for (i = 0; i < strlen(s) - 1; ++i)
		{

			if ((s[i] != ' ') && (!isdigit(s[i])))
				return 0;
			if (s[i] == ' ')
				ct++;
		}
		if (1 != ct)
			return 0;
		char first[3];
		char second[3];
		first[0] = 'x';
		first[1] = 'x';
		second[0] = 'x';
		second[1] = 'x';
		first[2] = '\0';
		second[2] = '\0';
		i = 0;
		j = 0;
		while (isdigit(s[i]))
		{
			first[j] = s[i];
			++i;
			++j;
		}
		++i;
		j = 0;
		while (isdigit(s[i]))
		{
			second[j] = s[i];
			++i;
			++j;
		}
		x = atoi(first);
		y = atoi(second);
		if ((x > height - 1) || (y > width - 1))
			return 0;
		field[x][y] = alive;
	}
	free (s);
	return 1;
}
void print (int **field1, int height, int width) /* функция, печатающая заданный двумерный динамический массив */
{
	int i = 0;
	int j = 0;
	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			char toprint = 0;
			switch(field1[i][j])
			{
				case alive:
					toprint = livingchar;
					break;
				case dead:
					toprint = deadchar;
					break;
				default:
					assert(0);
			}
			printf ("%c", toprint);
		}
		printf ("\n");
	}
	printf ("\n");
}
int count (int **field1, int i, int j, int height, int width) /* функция, считающая число живых соседей любой клетки,
параметры - таблица (двумерный массив) обитания клетки, координата строки, координата столбца - соответственно */
{
	int ct = 0;
	if (alive == field1[(i-1+height)%height][(j-1+width)%width])
		++ct;
	if (alive == field1[(i-1+height)%height][j])
		++ct;
	if (alive == field1[(i-1+height)%height][(j+1)%width])
		++ct;
	if (alive == field1[i][(j-1+width)%width])
		++ct;
	if (alive == field1[i][(j+1)%width])
		++ct;
	if (alive == field1[(i+1)%height][(j-1+width)%width])
		++ct;
	if (alive == field1[(i+1)%height][j])
		++ct;
	if (alive == field1[(i+1)%height][(j+1)%width])
		++ct;
	return ct;
}
void recount(int **field1, int **field2, int height, int width, int *rules) /* функция для пересчета соседей
каждой клетки, изменения и печати массива ТЕКУЩЕГО поколения с измененными клетками для двух массивов - 
ТЕКУЩЕГО и ПРЕДЫДУЩЕГО поколений соответственно */
{
	int i = 0;
	int j = 0;
	memcpy (field2, field1, sizeof(char)*height*width);
	int **arrct = (int**)calloc(height, sizeof(int*));
	for (i = 0; i < height; ++i)
	{
		arrct[i] = (int*)calloc(width, sizeof(int));
		for (j = 0; j < width; ++j)
		{
			arrct[i][j] = count(field2, i, j, height, width);
		}
	}
	for (i = 0; i < height; ++i) /* пересчитываем соседей для каждой клетки соответственно
	нашему стандарту B3/S23 в четырех случаях (по два на живую и неживую)
    и записываем переписанные значения в массив ТЕКУЩЕГО поколения */
    {
		for (j = 0; j < width; ++j)
		{
			if (field2[i][j] == dead)
			{
				if (1 == rules[arrct[i][j]])
					field1[i][j] = alive;
				else
					field1[i][j] = dead;
			}
			else
			{		
				if (1 == rules[arrct[i][j]+9])
					field1[i][j] = alive;
				else
					field1[i][j] = dead;
						
			}
		}
    }
	free(arrct);
	print(field1, height, width);
}
int main(int argc, char** argv) 
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
    int * rules = calloc (18, sizeof(int));
    rules = checkrules(input_file, rules);
    if (NULL == rules)
    {
    	printf("Wrong rules format; you should write it like 'R# Bxyz/Sxyz', using only digits and allowed symbols\n");
    	free (rules);
    	fclose (input_file);
    	return -1;
    }
    int * size = calloc (2, sizeof(int));
    size = checksize (input_file, size);
    if (NULL == size)
    {
    	printf("Wrong size format; you should write it like 'Size# x y', using only digits and allowed symbols, 3<=x,y<=50\n");
    	free (rules);
    	free (size);
    	fclose (input_file);
    	return -1;
    }
    int height = size[0];
    int width = size[1];
    free (size);
    int i = 0;
    int j = 0;
    int **field1 = (int**)calloc(height, sizeof(int*));  
    int **field2 = (int**)calloc(height, sizeof(int*));  
    for(i = 0; i < height; ++i) 
    {
  		field1[i] = (int*)calloc(width, sizeof(int));
  		field2[i] = (int*)calloc(width, sizeof(int)); 
    	for(j=0; j<width; ++j)  
      	{
      		field1[i][j] = dead; 
      	}
    }
	
    if (0 == livenup(field1, height, width, input_file))
    {
    	printf("Wrong coordinates format; print it like 'x y' every string, using only digits and one space, ");
    	printf("0 <= x <= height - 1, 0 <= y <= width - 1\n");
    	free (rules);
    	fclose (input_file);
    	return -1;
    }
	print(field1, height, width);
    memcpy(field2, field1, sizeof(char)*height*width);
    printf ("To end the game, put e, to continue the game - press any other button\n");
    char c = ' ';
    scanf ("%c", &c);
    while (c != 'e')
    {
   		recount (field1, field2, height, width, rules);
   		scanf ("%c", &c);
    }
    free(field1); 
    free(field2);
	free (rules);
	fclose (input_file);
    return 0; 
}