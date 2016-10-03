#include <stdio.h>
int main ()
{
	int size = 0;
	scanf ("%d", &size);
	int * arr;
	arr = (int*) calloc (size, sizeof(int));
	/* arr = (int*) free (arr);   --- строка, вызывающая runtimeerror после освобождения памяти и попытки напечатать элементы массива */
	int i = 0;
	for (i = 0; i < size; i++)
	{
		printf ("%d\n", arr[i]);
	}
	return 0;
}