#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "input.h"
#include "graph.h"
#include "int_vertex.h"
#include "point_vertex.h"


int main ()
{
	/*std::vector<int> arr;
	for (int i = 0; i < 12; ++i)
	{
		arr.push_back(i);
	}
	depth(arr, 0, INT_get_neighbors, INT_print);
	std::cout << std::endl << std::endl;
	breadth(arr, 0, INT_get_neighbors, INT_print);*/

	std::vector<struct Point> points;
	std::string str;
    std::ifstream input;
    input.open("qwe.txt");
    while (getline(input, str))
    {
        Key key = str;
        Value value;
        getkey(str, key);
        getvalue(str, value);
        struct Point to_push;
        to_push.name = key;
        to_push.distance = value.age;
        to_push.population = value.weight;
        points.push_back(to_push);
    }
    input.close();
    depth(points, 0, POINT_get_neighbors, POINT_print);
    std::cout << std::endl << std::endl;
    breadth(points, 0, POINT_get_neighbors, POINT_print);
    std::cout << std::endl << std::endl;
	
}