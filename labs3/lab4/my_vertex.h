#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct City {
	public:
		std::string getName() { return name; }
		int hetDistance() { return distance; }
		bool operator==(City & other)
		{
			if ((other.name == name) && (other.distance == distance))
			{
				return true;
			}
			return false;
		}
	//private:	
		std::string name;
		int distance;
};

std::vector<City> MY_get_neighbors (std::vector<City> arr, City index) 
{
	std::vector<City> result;
	for (int i = 0; i < arr.size(); ++i)
	{
		if ((std::abs(arr[i].distance - index.distance) != 0) && (std::abs(arr[i].distance - index.distance) <= 2))
		{
			result.push_back(arr[i]);
		}
	}
	return result;
}

void MY_print(City value)
{
	std::cout << value.name << " " << value.distance << " ";
}