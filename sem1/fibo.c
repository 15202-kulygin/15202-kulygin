#include <stdio.h>
int fibo (int x) /* Функция для нахождения значения х-числа Фибоначчи */
{ 
	int f=1;
	if (x>2)
	{
 		f=fibo(x-1)+fibo(x-2);
 		x--;
 	}
	return f;
}
	int main (){
	int n;
	printf ("Put in a number of Fibonacci's to print:");
	scanf ("%d", &n);
	int p=n;
	int F[n]; 
	while (p>0)
		{
			F[p]=fibo(p);
			p--;
		}
		int c=1;
	while (c<n+1)
		{
		printf ("%d ", fibo(c));
		c++;
		}
		printf ("\n:");
		system ("pause");
	return 0;
}