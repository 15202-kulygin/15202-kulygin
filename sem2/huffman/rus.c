#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char ** argv)
{
	long long int k = 4095;
	unsigned int a = 4095;
	int i = 0;
	for (i = 0; i < 64; ++i)
	{
		int mask = 1 << (64 - i - 1);
		printf("%d", (int)((k & mask) >> (64-i-1)));
	}
	printf("\n");
	printf("%d size\n", sizeof(int));
	for (i = 0; i < 32; ++i)
	{
		int mask = 1 << (32 - i - 1);
		printf("%d", (int)((a & mask) >> (32-i-1)));
	}
	return 0;
}