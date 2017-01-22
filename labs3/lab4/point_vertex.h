#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct Point {
	std::string name;
	int distance;
	int population;
};

std::vector<int> POINT_get_neighbors (std::vector<Point> arr, int index) 
{
	std::vector<int> result;
	for (int i = 0; i < arr.size(); ++i)
	{
		if ((abs(arr[i].distance - arr[index].distance) <= 1) && (abs(arr[i].distance - arr[index].distance) != 0)) 
		{
			result.push_back(i);
		}
	}
	return result;
}

void POINT_print(Point to_print)
{
	std::cout << to_print.name << " " << to_print.distance << " " << to_print.population << " "; 
}