#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



// 125 000 000	--- 	15s
// 300 000 000	---		30s

// относительная погрешность = 1% при времени выполнения программи порядка 15 секунд, т.е. абсолютная погрешность для данной программы = 0.15s

double pi_number (double n)
{
	int i = 0;
	double result = 0;
	for (i = 0; i <= n; ++i)
	{
		result += 4 * pow(-1, i) / (2 * i + 1);
	}
	return result;
}

int main()
{
	//printf("Put int the n parameter (~300000000):\n");
	double n = 0;
	//scanf("%lf", &n);
	for (n = 250000000; n <= 500000000; n += 50000000)
	{
		struct timespec start;
		struct timespec end;
		system("sync");
		clock_gettime(CLOCK_MONOTONIC_RAW, &start);
		double result = pi_number(n);
		clock_gettime(CLOCK_MONOTONIC_RAW, &end);
		printf("Result for n = %.0f: %f\n", n, result);
		printf("Time : %lf sec\n", end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));
		if (n == 400000000)
		{
			n += 50000000;
		}
	}
	
}