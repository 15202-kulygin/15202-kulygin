#include <stdio.h>
#include <math.h>

// cat /proc/cpuinfo

// 1 330 000 000

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
	union ticks {
		unsigned long long t64;
		struct s32 { long th, tl; } t32;
	} start, end;
	double cpu_Hz = 1330000000ULL;
	printf("Put int the n parameter :\n");
	double n = 0;
	scanf("%lf", &n);
	asm("rdtsc\n":"=a"(start.t32.th),"=d"(start.t32.tl));
	double result = pi_number(n);
	asm("rdtsc\n":"=a"(end.t32.th),"=d"(end.t32.tl));
	printf("Result : %f\n", result);
	printf("Time : %lf sec\n", (end.t64 - start.t64)/cpu_Hz);
}