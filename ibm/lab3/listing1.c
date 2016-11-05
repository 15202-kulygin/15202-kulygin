#include <stdio.h>
float power(float x,int n)
{ 
  int i;
  float s;
  s=1;
  for (i=0;i<n;i++) s=s*x;
  return s;
}
 
int main()
{ 
  float y;
  y=power(2.125,10);
  printf("Result: %f\n",y);
  return 0;
}
