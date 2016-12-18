#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/times.h> 
#include <unistd.h> 
#include <stdint.h>

#define K 50
#define N 256

int main()
{
  int n = N;
  int to_read = 0;
  for (int j = 0; j < 18; j++)
  {
    int * array = (int*) calloc(n, sizeof(int));
    uint32_t hi, lo, hi2, lo2;
    int min = 1000000;


    //********* direct ordered array
    for (int i = 0; i < n; i++) 
    {
      array[i] = (i + 1) % n;
    }

  

      to_read = 0;
      __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
      uint64_t start2 = ( (uint64_t) lo) | ( ((uint64_t) hi) << 32 );
      for (int i = 0; i < n*K; i++)
      {
        to_read = array[to_read];
      }
      __asm__ __volatile__ ("rdtsc" : "=a" (lo2), "=d" (hi2));
      uint64_t end2 = ( (uint64_t) lo2) | ( ((uint64_t) hi2) << 32 );
      if (((end2-start2)/(n*K)) < min)
      {
        min = (end2-start2) / (n*K);
      }
    
    printf("Size %d\nDirect order time : %d tacts/elem\n", n, min);
    //**********









   
    
    n *= 2;
  }
  return 0;
}