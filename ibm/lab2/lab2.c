#include <stdio.h>
#include <math.h>



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
	printf("Put int the n parameter (~300000000):\n");
	double n = 0;
	scanf("%lf", &n);
	double result = pi_number(n);
	printf("Result : %f\n", result);
}