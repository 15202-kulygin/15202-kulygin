#include <stdio.h>
#include <stdint.h>

int main(void)
{
	int32_t summ1 = 1;
	int32_t summ2 = 1;

	FILE* fib_file = fopen("test_fibonachi.txt", "w");

	// for (int32_t i = 0; i < 46; i+=2)	//4.5 GB
	// for (int32_t i = 0; i < 40; i+=2)	//1.7 GB
	for (int32_t i = 0; i < 40; i+=2)	//669 MB
	{
		//Write summ1 letters
		for (int32_t j = 0; j < summ1; j++)
		{
			fputc('a' + i, fib_file);
		}

		//Write summ2 letters
		for (int32_t j = 0; j < summ2; j++)
		{
			fputc('a' + i + 1, fib_file);
		}

		summ1 = summ1 + summ2;
		summ2 = summ2 + summ1;
	}

	fclose(fib_file);
	return 0;
}
