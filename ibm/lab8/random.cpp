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


    











    //********* random ordered array
    srand(time(NULL));
    int pos = 0;
    int * shuffled = (int *) calloc (n, sizeof(int));
    for (int i = n; i > -1; i--) 
    {
      shuffled[i] = -1;
    }
    for (int i = 0; i < n; i++) 
    {
      pos = rand() % n;
      while (shuffled[pos] != -1)
      {
        pos++;
        if(pos == n)
        {
          pos = 0;
        }
      }
      shuffled[pos] = i;
    }
    for (int i = 0; i < n; ++i)
    {
      array[shuffled[i]] = shuffled[(i+1)%n];
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
    printf("Random order time : %d tacts/elem\n\n", min);
    min = 1000000;
    //**********
    
    n *= 2;
  }
  return 0;
}