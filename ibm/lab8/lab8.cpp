#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/times.h> 
#include <unistd.h> 
#include <stdint.h>

//g++ -O1 lab8.cpp


#define K 1024
#define N 256

int to_read2 = 0;

int main()
{
  int n = N;
  int to_read = 0;
  for (int j = 0; j < 18; j++)
  {
    int * array = (int*) calloc(n, sizeof(int));
    uint64_t hi, lo, hi2, lo2;
    uint64_t min = 1000000;


    //********* direct ordered array
    for (int i = 0; i < n; i++) 
    {
      array[i] = (i + 1) % n;
    }


    for (int i = 0; i < n; i++) // heating
    {
        //to_read = array[to_read];
        to_read2 = array[to_read2];
    }
    for (int l = 0; l < K; ++l)
    {
        to_read2 = 0;
        to_read = 0;
        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
        uint64_t start2 = ( (uint64_t) lo) | ( ((uint64_t) hi) << 32 );
        for (int i = 0; i < n; i++)
          {
            to_read = array[to_read];
            to_read2 = array[to_read2];
          }
          __asm__ __volatile__ ("rdtsc" : "=a" (lo2), "=d" (hi2));
          uint64_t end2 = ( (uint64_t) lo2) | ( ((uint64_t) hi2) << 32 );
          if (((end2-start2)/(n)) < min)
          {
            min = (end2-start2) / (n);
          }
    }
    
        printf("Size %d\nDirect order time : %lu tacts/elem\n", n, min);
        min = 1000000;
    //**********









    //********* reverse ordered array
    for (int i = 0; i < n; i++) 
    {
      array[i] = (i - 1) % n;
    }

      
    for (int i = 0; i < n; i++) // heating
    {
        to_read = array[to_read];
        to_read2 = array[to_read2];
    }
    for (int l = 0; l < K; ++l)
    {
        to_read2 = 0;
        to_read = 0;
        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
        uint64_t start2 = ( (uint64_t) lo) | ( ((uint64_t) hi) << 32 );
        for (int i = 0; i < n; i++)
          {
            //to_read = array[to_read];
            to_read2 = array[to_read2];

          }
          __asm__ __volatile__ ("rdtsc" : "=a" (lo2), "=d" (hi2));
          uint64_t end2 = ( (uint64_t) lo2) | ( ((uint64_t) hi2) << 32 );
          if (((end2-start2)/(n)) < min)
          {
            min = (end2-start2) / (n);
          }
    }
    
    printf("Reverse order time : %lu tacts/elem\n", min);
    min = 1000;
    //**********












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

      
    for (int i = 0; i < n; i++) // heating
    {
        //to_read = array[to_read];
        to_read2 = array[to_read2];
    }
    for (int l = 0; l < K; ++l)
    {
        to_read2 = 0;
        to_read = 0;
        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
        uint64_t start2 = ( (uint64_t) lo) | ( ((uint64_t) hi) << 32 );
        for (int i = 0; i < n; i++)
          {
            to_read = array[to_read];
            to_read2 = array[to_read2];
          }
          __asm__ __volatile__ ("rdtsc" : "=a" (lo2), "=d" (hi2));
          uint64_t end2 = ( (uint64_t) lo2) | ( ((uint64_t) hi2) << 32 );
          if (((end2-start2)/(n)) < min)
          {
            min = (end2-start2) / (n);
          }
    }
    printf("Random order time : %lu tacts/elem\n\n", min);
    min = 1000;
    //**********
    
    n *= 2;
  }
  return 0;
}
