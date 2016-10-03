#include <stdio.h>
int max (int x, int y)
{
	int max;
	if (x>y)
		max=x;
	else 
		max=y;
	return max;
}
int main ()
{
	printf ("Put in the number of array's elements: ");
	int n; 
	scanf ("%d", &n);
	printf ("Put in the array's elements: ");
	int a[n];

	int i;
	for (i=0; i<n; i++)
	{
	scanf ("%d", &a[i]);
	}
	
	int maximum=a[0];
	for (i=0; i<n-1; i++)
	{
	if (max(a[i], a[i+1])>maximum)
		maximum=max(a[i], a[i+1]);
	}
	printf ("%d\n", maximum);
    system ("pause");
	return 0;
}