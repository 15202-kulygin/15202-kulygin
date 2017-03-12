#include <stdio.h>
#include <math.h>

int main()
{
	printf("Put in the x:\n");
	double x = 0;
	int rc = scanf("%lf", &x);
	if ((1.0 >= x) || (0 == rc))
	{
		printf("Wrong x value\n\n");
		return -1;
	}
	double min_integer = ceil(log(x));
	double max_integer = floor(exp(x));
	double result = 0;
	while (min_integer <= max_integer)
	{
		result += min_integer * min_integer;
		int overflow_flag = fetestexcept(FE_OVERFLOW);
		if (overflow_flag)
		{
			printf("Double overflow\n\n");
			return -1;
		}
		min_integer++;
	}
	printf("The result is %.0f\n\n", result);
}
	