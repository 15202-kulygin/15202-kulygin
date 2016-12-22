#include <iostream>
#include <cstdlib>

#define FRAGMENTS_AMOUNT 40


unsigned long long timer(int *arr, int arrSize) {
    union ticks {
        unsigned long long t64;
        struct s32 {
            long th, tl;
        } t32;
    } start, end;

    unsigned  long long tmp = -1;
    for(int j = 0; j < 10; ++j) {
        asm("rdtsc\n":"=a"(start.t32.th), "=d"(start.t32.tl));
        for (int i = 0, index = 0, count = arrSize; i < count; ++i) {
            index = arr[index];
        }
        asm("rdtsc\n":"=a"(end.t32.th), "=d"(end.t32.tl));

        if(tmp > (end.t64 - start.t64)) {
            tmp = end.t64 - start.t64;
        }
    }

    return tmp / arrSize;
}


int to_read = 0;

int main() {
    int * results = (int *) calloc (FRAGMENTS_AMOUNT, sizeof(int));
    const int cacheSize = 3 * 1024 * 1024; 
    const int offset = cacheSize;
    for(int fragments = 1; fragments <= FRAGMENTS_AMOUNT; ++fragments) 
    {
       int arrSize = (fragments * offset) / sizeof(int);
       int * arr = (int *) calloc (arrSize, sizeof(int));
       int arrOffset = offset / sizeof(int);;
       for (int i = 0; i < fragments - 1; ++i) //FILLING
       {
            for (int j = 0; j < arrOffset; ++j)
            {
                arr[i*arrOffset + j] = ((i+1) % fragments) * arrOffset + j;
            }
       }
       for (int i = 0; i < arrOffset; ++i)
       {
            arr[(fragments - 1) * arrOffset + i] = (i + 1) % arrOffset;
       }

        

        /*uint64_t hi, lo, hi2, lo2;
        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
        uint64_t start = ( (uint64_t) lo) | ( ((uint64_t) hi) << 32 );
        int min = 1000;
        for (int k = 0; k < 10; ++k)
        {
            to_read = -1;
            for (int i = 0; i < arrSize; i++)
            {
                to_read = arr[to_read];
            }
            __asm__ __volatile__ ("rdtsc" : "=a" (lo2), "=d" (hi2));
            uint64_t end = ( (uint64_t) lo2) | ( ((uint64_t) hi2) << 32 );
            if ((end - start) / arrSize < min)
            {
                min = (end - start) / arrSize;
            }
        }*/


       results[fragments - 1] = timer(arr, arrSize);
       /*for (int i = 0; i < arrSize; ++i)
       {
        std::cout << arr[i] << " ";
       }
       std::cout << std::endl << std::endl;*/

    }


    for (int i = 0; i < FRAGMENTS_AMOUNT; ++i)
    {
        std::cout << i+1 << ") " << results[i] << std::endl;
    }
    std::cout << std::endl;
    return 0;
}