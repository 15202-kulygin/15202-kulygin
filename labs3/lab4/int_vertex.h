#include <iostream>
#include <vector>

std::vector<int> INT_get_neighbors (std::vector<int> arr, int index)
{
	std::vector<int> result;
	for (int i = 0; i < arr.size(); ++i)
	{
		result.push_back(i);
	}
	return result;
}

/*std::vector<int> INT_get_neighbors (std::vector<int> arr, int index) //TREE
{
	std::vector<int> result;
	if (0 == index)
	{
		result.push_back(7);
		result.push_back(6);
		result.push_back(1);
	}
	else if (1 == index)
	{
		result.push_back(5);
		result.push_back(2);
	}
	else if (2 == index)
	{
		result.push_back(4);
		result.push_back(3);
	}
	else if (7 == index)
	{
		result.push_back(11);
		result.push_back(8);
	}
	else if (8 == index)
	{
		result.push_back(10);
		result.push_back(9);
	}
	return result;
}*/

void INT_print(int value)
{
	std::cout << value << " "; 
}

int INT_get_size(std::vector<int> arr)
{
	return arr.size();
}