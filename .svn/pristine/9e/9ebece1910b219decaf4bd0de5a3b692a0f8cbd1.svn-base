#include <stdio.h>
#include <stdlib.h>
void swap (int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
void printmas (int *a, int n)
{
	int i = 0;
	for (i=0; i<n; ++i)
		printf ("%d ", a[i]);
	printf ("\n");
}
void recurs (int *a, int n, int nnow) {
	int i = 0;
	if (1 == nnow) 
	{
		printmas(a, n);
	}
	else {
		for (i=0; i<nnow-1; ++i) 
		{
			recurs (a, n, nnow-1);
			if (0 == nnow%2)
				swap(&a[i], &a[nnow-1]);
			else
				swap(&a[0], &a[nnow-1]);
		
		}
		recurs(a, n, nnow-1);
	}
}
int main ()
{
	int n = 0;
	int i = 0;
	scanf ("%d", &n);
	int *arr = (int*) calloc(n, sizeof(int));
	int nnow = n; 
	for (i=0; i<n; ++i)
		arr[i]=i+1;
	recurs (arr, n, nnow);
	return 0;
}

