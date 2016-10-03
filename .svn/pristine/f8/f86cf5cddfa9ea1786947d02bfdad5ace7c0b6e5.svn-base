#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMSIZE 64
#define FR 52
#define EX 11
#define SG 1

void printcases() /* печатаем начальные условия */
{
	printf ("Put int a decimal number to count its sign, exponent and fraction;\n");
	printf ("the number must have more than 0 and less than 18 digits at all\n");
	printf ("As the first symbol you can use '+' or nothing to put positive and '-' to put negative nums in\n");
	printf ("You can use '.' or ',' to separate integer from fraction\n");
}
int iscorrect(char * num) /* проверяем введенное число */
{
	int i = 0;
	int ct = 0;
	int havesign = 0;
	int len = strlen(num);
	for (i = 0; i < len - 1; ++i)
	{
		if ((!isdigit(num[i])) && (num[i] != '.') && (num[i] != ',') && (num[i] != '+') && (num[i] != '-'))
			return 0;
		if ((num[i] == '.') || (num[i] == ','))
			ct++;
		if (ct > 1)
			return 0;
		if ((num[i] == '-') || (num[i] == '+'))
			havesign++;
		if (havesign > 1)
			return 0;
		if (num[i] == ',')
			num[i] = '.';
	}
	if (0 == havesign)
	{
		if ((len < 2) || (len > 19))
			return 0;
	}
	else 
	{
		if ((len < 2) || (len > 20) || ((num[0] != '+') && (num[0] != '-')))
			return 0;
	}
	return 1;
}	
char sign(unsigned long long int prec) /* извлекает знак из двоичного представления */
{
	if (prec >> (NUMSIZE - SG) == 0)
		return '+';
	else
		return '-';
}
char * exponent(unsigned long long int prec) /* записывает двоичное представление порядка числа в строку */
{
	int i = EX;
	char * e = (char*) calloc (EX + 1, sizeof(char));
	while (i != 0)
	{
		e[EX - i] = (char)(((prec << (SG + EX - i)) >> (EX + FR)) + (int)('0'));
		i--;
	}
	e[EX] = '\0';
	return e;
}
int expdec(unsigned long long int prec) /* переводит битовое представление порядка в десятичное */
{
	int pw = 1024;
	int i = EX;
	int dec = 0;
	while (i != 0)
	{
		dec += ((prec << (SG + EX - i)) >> (EX + FR)) * pw;
		pw /= 2;
		i--;
	}
	return dec - 1023; 
}
char * fraction(unsigned long long int prec)
{
	int i = FR;
	char * f = (char*) calloc(FR + 1, sizeof(char));
	while (i != 0)
	{
		f[FR - i] = (char)(((prec << (SG + EX + FR - i)) >> (EX + FR)) + (int)('0'));
		i--;
	}
	f[FR] = '\0';
	return f;
}
double fractiondec(unsigned long long int prec) 
{
	double pw = 0.5;
	double fd = 0.0;
	int i = FR;
	while (i != 0)
	{
		fd += ((prec << (SG + EX + FR - i)) >> (EX + FR)) * pw;
		i--;
		pw /= 2;
	}
	return fd + 1;
}
void make(char * num) /* считает и выводит знак, порядок и мантиссу вещественного числа, записанного в строке */
{
	double numb = 0;
	numb = atof(num);
	unsigned long long int prec = 0;
	memcpy (&prec, &numb, sizeof(unsigned long long int)); /* копируем двоичное представление числа в инт, чтобы можно было применить
	битовые операции */
	char sig = sign(prec);
	int sigbinary = prec >> (NUMSIZE - SG);
	char * expon = exponent(prec);
	int expondec = expdec(prec);
	char * frac = fraction(prec);
	double fracdec = fractiondec(prec);
	printf ("\nSign: %c\nIn binary: %d\n\n", sig, sigbinary);
	printf ("Exponent in binary: %s\n", expon);
	printf ("Exponent in decimal: %d\n\n", expondec);
	printf ("Fraction in binary: 1,%s\n", frac);
	printf ("Fraction in decimal: %0.16llf\n", fracdec);
	printf ("\nTo get source number, you have to use following formula: N = M * 2^E ,\nwhere N stands for the number, M - for fraction in decimal, \n");
	printf ("E - for exponent in decimal\n");
	free(expon);
	free(frac);
	printf("\n");
}
int main()
{
	char * num = (char*) calloc (50, sizeof(char));
	printcases();
	while (1)
	{
		fgets (num, 50, stdin);
		if (0 == iscorrect(num))
			printf ("Incorrect number format, try again\n\n");
		else
			make(num);
	}
	free(num);
	return 0;
}