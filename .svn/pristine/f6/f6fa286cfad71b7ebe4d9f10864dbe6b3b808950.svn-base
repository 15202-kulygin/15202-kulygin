#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
char * get () /* функция для считывания строки из входного потока */
{
	char *a;
	a = (char *) malloc(1);
	char c;
	int i = 0;
	while ((c = getchar()) != '\n') 
	{
		a = realloc (a, i+1);
		a[i] = c;
		i++;
	}
	a[i] = '\0';
	return a;
}
int checkfrom(char *sfrom) /* функция для проверки строки
на соответствие основанию исходной системы счисления : 1, если строка корректна, иначе - 0 */
{
	if (('0' == sfrom[0]) || (0 == strlen(sfrom)))
		return 0;
	int i = 0;
	for (i = 0; i < strlen(sfrom); ++i)
	{
		if (!isdigit(sfrom[i])) 
			return 0;
	}
	int f = 0;
	f = atoi (sfrom);
	if ((2 > f) || (36 < f))
		return 0;
	return 1;
}
int checknum (char *snum, int from) /* функция, проверяющая на валидность введенное целое число в исходной системе счисления */
{
	int i; 
	int len = strlen(snum);
	if (len == 0)
		return 0;
	if ((len < 2) && ((snum[0] == '-') || (snum[0] == '+')))
		return 0;
	if (from <= 10)
	{
		i = ((snum[0] == '+') || (snum[0] == '-'));
		int num = 0;
		while (i < len)
		{	
			num = (int)(snum[i]) - (int)('0');
			if ((!isdigit(snum[i])) || (num >= from))
				return 0;
			++i;
		}		
	}
	else
	{
		i = ((snum[0] == '+') || (snum[0] == '-'));
		int Acode = (int)('A');
		char lastcode = Acode + (from - 11);
		while (i < len)
		{
			if (!isdigit(snum[i]))
			{
				int numcode = (int)(snum[i]);
				if ((numcode >= Acode) && (numcode <= lastcode))
					;
				else
					return 0;
			}
			++i;
		}
	}
	return 1;
}
char * change (char * snum) /* удаляет из строки символ знака и лишние нули, если они есть */
{
	int i = 0;
	int leng = strlen(snum);
	if ((snum[0] == '-') || (snum[0] == '+'))
	{	
		for (i = 0; i < leng - 1; ++i)
			snum[i] = snum[i+1];
		snum[i] = '\0';
	}
	i = 0;
	leng = strlen(snum);
	if ((snum[0] == '0') && (leng > 1))
	{
		while ((snum[i] == '0') && (i < leng))
			++i;
		int k = i;
		if (k == leng)
		{
			snum[0] = '0';
			snum[1] = '\0';
		}
		else
		{
			for (i = 0; i < leng - k; ++i)
			{
				snum[i] = snum[i + k];
			}
			snum[leng - k] = '\0';
		}
	}
	return snum;
}
long long int todec (char *snum, int from) /* функция, переводящая исходное число из исходной СИ в десятичную */
{
	long long int dec = 0;
	int i = 0;
	int code = 0;
	int maxpow = 1;
	for (i = 1; i <= strlen(snum) - 1; ++i)
 		maxpow *= from;
	for (i = 0; i < strlen(snum); ++i)
	{
		if (isdigit(snum[i]))
		{
			code = (int)(snum[i]) - (int)('0');
		}
		else 
		{
			code = (int)(snum[i]) - (int)('A') + 10;
		}
		dec = dec + code*maxpow;
		maxpow /= from;
	}	
	return dec;
}
char * newnumber (int number, int to) /* функция, переводящая исходное число из десятичной в требуемую и сохраняющая его в виде строки */
{
	int *newnum = (int*) calloc(1, sizeof(int));
	int i = 0;
	if (0 == number)
	{
		newnum[0] = 0;
	}
	else
	{
		while (0 != number)
		{
			newnum = (int*) realloc (newnum, (i+1) * (sizeof(int)));
			newnum[i] = number%to;
			number = number/to;
			i++;
		}
	}
	int size;
	if (0 == i)
		size = 1;
	else
		size = i;
	char *news = (char*) calloc (size+1, sizeof(char));
	for (i = 0; i < size; ++i)
	{
		if ((newnum[size-i-1] >= 0) && (newnum[size-i-1] <= 9))
			news[i] = (char)(newnum[size-i-1] + (int)('0'));
		else
		{
			news[i] = (char)(newnum[size-i-1] + (int)('A') - 10);
		}
	}
	news[i+1] = '\0';
	return news;
	free (newnum);
}
void make()
{
	printf("Put in one digit number as a radix of the source numeration, 1 =< radix <= 36\n");
	char * sfrom = get();
	if (0 == checkfrom(sfrom))
	{
		printf("Incorrect radix format\n\n");
		free(sfrom);
		return;
	}
	int from = atoi(sfrom);
	printf("Put in one digit number in the source numeration; use capital letters\n");
	char * snum = get();
	if (0 == checknum(snum, from))
	{
		printf("Incorrect number format\n\n");
		free(sfrom);
		free(snum);
		return;
	}
	char sign = ' ';
	if ((snum[0] == '-') || (snum[0] == '+'))
		sign = snum[0];
	snum = change(snum);
	long long int number = todec(snum, from);
	printf("Put in one digit number as a radix of the final numeration, 1 =< radix <= 36\n");
	char * sto = get();
	if (0 == checkfrom(sto))
	{
		printf("Incorrect radix format\n\n");
		free(sfrom);
		free(snum);
		free(sto);
		return;
	}
	int to = atoi(sto);
	char * newn = newnumber(number, to);
	if ('-' == sign)
	{
		printf("A number %c%s was converted from a numeration with radix %d\n", sign, snum, from);
		printf("to a numeration with radix %d as %c%s\n", to, sign, newn);
	}
	else
	{
		printf("A number %s was converted from a numeration with radix %d\n", snum, from);
		printf("to a numeration with radix %d as %s\n", to, newn);
	}
	printf("\n");
	free(sfrom);
	free(snum);
	free(sto);
	free(newn);
}
int main ()
{
	make : while (1)
	{
		printf("Put in one digit number as a radix of the source numeration, 1 =< radix <= 36\n");
		char * sfrom = get();
		if (0 == checkfrom(sfrom))
		{
			printf("Incorrect radix format\n\n");
			free(sfrom);
			goto make;
		}
		int from = atoi(sfrom);
		printf("Put in one digit number in the source numeration; use capital letters\n");
		char * snum = get();
		if (0 == checknum(snum, from))
		{
			printf("Incorrect number format\n\n");
			free(sfrom);
			free(snum);
			goto make;
		}
		char sign = ' ';
		if ((snum[0] == '-') || (snum[0] == '+'))
			sign = snum[0];
		snum = change(snum);
		long long int number = todec(snum, from);
		printf("Put in one digit number as a radix of the final numeration, 1 =< radix <= 36\n");
		char * sto = get();
		if (0 == checkfrom(sto))
		{
			printf("Incorrect radix format\n\n");
			free(sfrom);
			free(snum);
			free(sto);
			goto make;
		}
		int to = atoi(sto);
		char * newn = newnumber(number, to);
		if ('-' == sign)
		{
			printf("A number %c%s was converted from a numeration with radix %d\n", sign, snum, from);
			printf("to a numeration with radix %d as %c%s\n", to, sign, newn);
		}
		else
		{
			printf("A number %s was converted from a numeration with radix %d\n", snum, from);
			printf("to a numeration with radix %d as %s\n", to, newn);
		}
		printf("\n");
		free(sfrom);
		free(snum);
		free(sto);
		free(newn);
	}
	return 0;
}