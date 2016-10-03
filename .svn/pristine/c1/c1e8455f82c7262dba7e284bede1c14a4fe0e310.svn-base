#include <stdio.h>

int factorial (int x){
	int f=1;
	int i=0;
	while (i<x)
		{
		i++;
		factorial=i*factorial;
		}
	return factorial;
	}

int recursive (int x){
	int recurs=1;
	if (x>1){
		recurs=x*recursive(x-1);
		x--;
		}
	return recurs;
	}
	

int main (){
	printf ("%d\n", factorial(5));
	printf ("%d\n", recursive(5));
	return 0;
	}