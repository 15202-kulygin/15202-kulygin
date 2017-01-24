#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include "graph.h"
#include "int_vertex.h"
#include "my_vertex.h"


int main ()
{
    std::cout << "INT" << std::endl;
	std::list<int> arr;
	for (int i = 0; i < 12; ++i)
	{
		arr.push_back(i);
	}
	depth(0, arr, INT_get_neighbors, INT_print);
	breadth(0, arr, INT_get_neighbors, INT_print);
    
    std::cout << "CITY" << std::endl;
    std::vector<City> cities = {{"a", 0}, {"b", 1}, {"c", 1}, {"d", 2}, {"f", 4}, {"e", 4}};
    City start = {"a", 0};
    depth(start, cities, MY_get_neighbors, MY_print);
    breadth(start, cities, MY_get_neighbors, MY_print);	
}