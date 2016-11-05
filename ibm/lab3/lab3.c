#include <stdio.h>
#include <math.h>
#include <time.h>

// rip-relative ---- для лабы

// 125 000 000	 --- 	15s

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
	printf("Put int the n parameter :\n");
	double n = 0;
	scanf("%lf", &n);
	struct timespec start;
	struct timespec end;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	double result = pi_number(n);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	printf("Result : %f\n", result);
	printf("Time : %lf sec\n", end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));
}