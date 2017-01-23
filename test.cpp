#include <iostream>
#include <cstring>
#include <string>

void reverse(char * str)
{
	int len = strlen(str);
	char temp[len];
	for (int i = 0; i < len; ++i)
	{
		temp[i] = str[len - i - 1];
	}
	std::copy(temp, temp+len, str);
}

int main()
{
	char * str = new char [3];
	str[0] = 'q';
	str[1] = 'w';
	str[2] = 'e';
	std::cout << str << std::endl;
	reverse(str);
	std::cout << str;
	delete [] str;
}