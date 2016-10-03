#include <stdio.h>
#define SIZE 40

long long int routect (int x)
{
	long long int route[SIZE+1][SIZE+1];
	int i = 0;
	while (i < SIZE)
	{
		route[i][0] = 1;
		route[0][SIZE-i] = 1;
		i++;
	}
	i = 1;
	int j = 1;
	while (i < SIZE)
	{
		while (j < SIZE)
		{	
			route[i][j] = route[i-1][j] + route[i][j-1];
			j++;
		}
		j = 1;
		i++;
	}
	return route[x][x]; 
}

int main()
{
	printf ("%lld", routect(20));
	return 0;
}