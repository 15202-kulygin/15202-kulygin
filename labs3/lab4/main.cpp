#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "input.h"
#include "graph.h"
#include "int_vertex.h"


int main ()
{
	std::vector<int> arr;
	for (int i = 0; i < 2; ++i)
	{
		arr.push_back(i);
	}
	depth(0, arr, INT_get_neighbors, INT_print);
	std::cout << std::endl << std::endl;
	//breadth(1, arr, INT_get_neighbors, INT_print);

	/*std::vector<int> arr;
	arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    depth(1, arr, INT_get_neighbors, INT_print);
    std::cout << std::endl << std::endl;
    //breadth(points, 0, POINT_get_neighbors, POINT_print);
    std::cout << std::endl << std::endl;*/
	
}