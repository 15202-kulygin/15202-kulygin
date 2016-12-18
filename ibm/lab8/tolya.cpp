#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/times.h> // for times
#include <unistd.h> // for sysconf
#include <stdint.h>

#define K 1000
int main(){
  int n=256;
  int k,i,l;
  for (int j=0;j<16;j++){
  int *a=(int*)calloc(n,sizeof(int));
  int pos=0;
  srand(time(NULL));
  for (i=0;i<n;i++){
    a[i]=-1;
  }
  for (i=0;i<n;i++){
    pos=rand()%n;
    while(a[pos]!=-1){
      pos++;
      if(pos==n){
        pos=0;
      }
    }
    a[pos]=i;
  }
  uint32_t hi, lo,hi2,lo2,min=10000000;
  for (l=0;l<K;l++){
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    uint64_t start2 = ( (uint64_t) lo) | ( ((uint64_t) hi) << 32 );
    for (i=n;i>-1;i--){
      k=a[k];
    }
    __asm__ __volatile__ ("rdtsc" : "=a" (lo2), "=d" (hi2));
    uint64_t end2 = ( (uint64_t) lo2) | ( ((uint64_t) hi2) << 32 );
    if (((end2-start2)/n) < min){
      min=(end2-start2)/n;
    }
  }
  printf("(proc_time)Time taken for %d elements: %lu tacts.\n",
  n,min);
  n=n*2;
  }
  return 0;
}
