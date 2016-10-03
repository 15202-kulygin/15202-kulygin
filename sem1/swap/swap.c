#include <stdio.h>

void swap (int * x, int * y)
{
	int temp = 0;
	temp = *x;
	*x = *y;
	*y = temp;
}

int main ()
{
	int a = 0;
	int b = 0;
	scanf ("%d %d", &a, &b);
	swap (&a, &b);
	printf ("%d %d\n", a, b);
	return 0;
}