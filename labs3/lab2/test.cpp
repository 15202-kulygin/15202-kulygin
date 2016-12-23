
#include <iostream>
#include <memory>



int main (int argc, char ** argv)
{
	int * q = new int[10];
	q[5] = 777;
	std::unique_ptr<int> a = std::unique_ptr<int>(q);

	std::cout << a.get()[5];
}