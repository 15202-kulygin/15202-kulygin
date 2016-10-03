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
int main()
{
  int n = 0;
  scanf ("%d", &n);
  int *a = (int*) calloc(n, sizeof(int));
  int *p = (int*) calloc(n, sizeof(int));
  int i = 0;
  for (i = 0; i < n; ++i)
  {
  	a[i] = i + 1 ;
  	p[i] = 0;
  }
  printmas (a, n);
    i = 1;
  int j = 0;
  while(i < n) 
  {
      if (p[i] < i) 
      {
         j = i % 2 * p[i];   
         swap(&a[j], &a[i]);
         printmas (a, n);
         p[i]++;            
         i = 1;              
      } 
      else 
      {               
         p[i] = 0;           
         i++;              
      } 
   } 
   return 0;
} 