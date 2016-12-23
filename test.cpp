#include <iostream>

int main()
{
	int * a = new int[10];
	std::fill(a, a + 10, 777);
	for (int i = 0; i < 10; ++i)
	{
		std::cout << a[i] << " ";
	}
}