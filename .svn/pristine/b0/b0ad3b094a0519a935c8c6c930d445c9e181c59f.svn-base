#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void skipwp(char * s, int * pos) // перемещает указатель строки на первый непробельный символ
{
	while (s[*pos] == ' ')
		(*pos)++;
}
int * count (char * s) // считает количество переменных и дизъюнкций в формуле
{
	int pos = 0;
	int len = strlen(s);
	int varct = 0;
	int dizct = 0;
	char * vars = (char *) calloc (1, sizeof(char));
	while (pos < len) 
	{
		if ('(' == s[pos])
			dizct++;
		else if (isalpha(s[pos]))
		{
			int i = 0;
			int check = 0;
			for (i = 0; i < varct; ++i)
				if (vars[i] == s[pos])
					check = 1;
			if (0 == check)
			{
				varct++;
				vars = (char *) realloc (vars, varct*sizeof(char));
				vars[varct-1] = s[pos];
			}
		}
		pos++;
	}
	free(vars);
	vars = NULL;
	int * counted = (int *) calloc (2, sizeof(int));
	counted[0] = dizct;
	counted[1] = varct;
	return counted;
}
int ** makeformula(char * s, int dizct, int varct) // создает по формуле, заданной строкой, формулу, заданную двумерным массивом целых + массив для означивания
{
	int pos = 0;
	int len = strlen(s);
	char * vars = (char *) calloc (varct, sizeof(char));
	int i = 0;
	for (i = 0; i < varct; ++i)
		vars[i] = ' ';
	int v = 0;
	while (pos < len) // заполняем массив переменных
	{
		if (isalpha(s[pos]))
		{
			int i = 0;
			int check = 0;
			for (i = 0; i < varct; ++i)
				if (vars[i] == s[pos])
					check = 1;
			if (0 == check)
			{
				vars[v] = s[pos];
				v++;
			}
		}
		pos++;
	}
	int ** form = (int **) calloc (dizct, sizeof(int *));
	for (i = 0; i < dizct; ++i)
		form[i] = (int *) calloc (varct, sizeof(int));
	int j = 0;
	for (i = 0; i < dizct; ++i) // определяем любую переменную в дизъюнкции как отсутствующую
		for(j = 0; j < varct; ++j)
			form[i][j] = 0;
	pos = 0;
	skipwp(s, &pos);
	int d = 0;
	while (pos < len) // заполняем все дизъюнкции массива переменными
	{
		if (s[pos] == '(')
		{
			d++;
			pos++;
		}
		int v = 0;
		skipwp(s, &pos);
		while (s[pos] != ')')
		{
			int denial = 0;
			if (s[pos] == '!')
			{
				pos++;
				denial = 1;
			}
			if (isalpha(s[pos]))
			{
				int num = 0;
				int i = 0;
				while (1)
				{
					if (vars[i] == s[pos])
					{
						num = i+1;
						break;
					}
					++i;
				}
				if (0 == denial)
					form[d-1][v] = num;
				else 
					form[d-1][v] = -num;
				v++;
			}
			skipwp(s, &pos);
			pos++;
			skipwp(s, &pos);
		}
		pos++;
		skipwp(s, &pos);
		pos++;
		skipwp(s, &pos);
	}
	return form;
}
int dpll (int ** formula, int * interp, int dizct, int varct, int assigned, int propagated)
{

	if ((propagated + assigned) >= varct) 
	{
		if (checkinterp (formula, interp, dizct, varct))
			return 1;
		else 
			return 0;
	}
	assigned++;
	propagated += propagation (formula, interp, dizct, varct);
	if ((propagated + assigned) >= varct)
		if (checkinterp (formula, interp, dizct, varct) == 1)
			return 1;
	int indextoassign = assigned;
	int i = 0;
	for (i = 0; i < varct; i++) 
	{
		if (interp[i] == 2)
		{
			indextoassign = i;
			break;
		}
	}
	/*if (interp[indextoassign] != 2) {
		if (dpll (formula, interp, dizct, varct, assigned, propagated)) {
			return 1;
		} else {
			return 0;
		}
	}*/
	interp [indextoassign] = 1; 
	if (dpll (formula, interp, dizct, varct, assigned, propagated)) 
		return 1;
	interp [indextoassign] = 0;
	if (dpll (formula, interp, dizct, varct, assigned, propagated)) 
		return 1;
	interp [indextoassign] = 2;
	return 0;
}
int propagation (int ** formula, int * interp, int dizct, int varct)
{
	int  i = 0;
	int j = 0;
	int singledizct = 0;
    	
    for (i = 0; i < dizct; i++) 
	{
		int count = 0;
		int temp = 0;
		for (j = 0; j < varct; j++) 
		{
			if (formula[i][j] != 0) 
				count++;
			if (0 == j)
				temp = formula[i][j];
		}
		int ind = abs(temp) - 1;
		if ((count == 1) && (interp[ind] == 2))
		{
			singledizct++;
			if (temp < 0)
				interp[ind] = 0;
			else 
				interp[ind] = 1;
		}
	}
	int puredizct = 0;
	int mark[varct];
	for (i = 0; i < varct; i++)
		mark[i] = 0;
	for (i = 0; i < dizct; i++) 
	{
		for (j = 0; j < varct; j++) 
		{
			int ind = abs(formula[i][j]) - 1;
			if (ind >= 0) /// ???????
			{				
				if ((mark[ind] == 0) && (interp[ind] == 2))
				{
					if (formula[i][j] > 0) 
						mark[ind] = 1;
					if (formula[i][j] < 0) 
						mark[ind] = -1;
				} 
				else 
					if (formula[i][j] * mark[ind] < 0) 
						mark[ind] = 3;
			}
		}
	}
	for (i = 0; i < varct; i++) 
	{
		if ((mark[i] != 3) && (interp[i] == 2)) 
		{
			if (mark[i] > 0) 
				interp[i] = 1;
			else
				interp[i] = 0;
			puredizct++;
		}
	}
	return singledizct + puredizct;
	
}
int checkinterp(int ** formula, int * interp, int dizct, int varct)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < dizct; i++) {
		int tmp = 0;
		for (j = 0; j < varct; j++) {
			if (formula[i][j] != 0) 
			{
				if (((formula[i][j] > 0) && (interp[abs(formula[i][j])-1] == 1)) || ((formula[i][j] < 0) && (interp[abs(formula[i][j])-1] == 0)))
					tmp = 1;
				continue;
			}
		}
		if (0 == tmp) {
			return 0;
		}
	}
	return 1;
}
int main ()
{
	printf("Put in the formulae in cnf:\n");
	char * s = (char *) calloc (50, sizeof(char));
	gets(s);
	int * counted = count(s);
	int dizct = counted[0];
	int varct = counted[1];
	free(counted);
	int ** formula = makeformula(s, dizct, varct); // создание формулы в виде двумерного массива целых из строки
	free(s);
	int * interp = (int *) calloc (varct, sizeof(int)); // массив для означивания
	// interp[i] - означивание переменной под номером i, где i =  0<->x, 1<->y, 2<->z
	// при означивании : 0 - ложь, 1 - истина, 2 - неизвестно
	int i = 0;
	for (i = 0; i < varct; ++i)
		interp[i] = 2;
	for (i = 0; i < dizct; ++i) // 1 -- x; 2 -- y; 3 -- z; 0 - не входит
	{
		int j = 0;
		for (j = 0; j < varct; ++j)
			printf("%d ", formula[i][j]);
		printf("\n");
	}
	if (1 == dpll(formula, interp, dizct, varct, 0, 0))
	{
		int k = 0;
		for (k = 0; k < varct; ++k)
		{
			printf("Value of the %d variable : ", k+1);
			if (0 == interp[k])
				printf("false\n");
			if (1 == interp[k])
				printf("true\n");
			if (2 == interp[k])
				printf("not stated\n");
		}
	}
	else
	{
		printf("This cnf is not satisfiable\n");
	}
	for (i = 0; i < dizct; ++i)
	{
		free(formula[i]);
	}
	free (formula);
	free(interp);
	return 0;
}