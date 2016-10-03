#include <stdio.h>
int main ()
{
	int size = 0;
	scanf ("%d", &size);
	int * arr;
	arr =(int*) calloc (size, sizeof(int));
	int left = 1000; /* При запрашивания как минимум от 1000 элементов за краем массива - ошибка времени выполнения */
	int right = 1000;
	int i = 0;
	printf ("Printing %d arr's elements behind the left edge: \n", left);
	for (i = 0; i < left; i++)
	{
		printf ( "%d\n", arr[0-i]);
	}
	printf ("Printing %d arr's elements behind the right edge: \n", right);
	for (i = 0; i < right; i++)
	{
		printf ( "%d\n", arr[size+i]);
	}
	return 0;
}