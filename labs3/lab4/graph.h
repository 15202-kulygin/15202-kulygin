#include <iostream>
#include <vector>
#include <stack>
#include <queue>

template <class T> struct Vertex {
	std::vector< Vertex <T> * > neighbors;
	T data;
	bool is_visited;	
};


template <class T> void depth(std::vector<T> source, int start_index, std::vector<int> (* get_neighbors)(std::vector<T> arr, int index), void (*print)(T value))
{
	int size = source.size();
	std::vector< Vertex<T> > graph(size);
	for (int i = 0; i < size; ++i)
	{
		graph[i].data = source[i];
		graph[i].is_visited = false;
	}
	for (int i = 0; i < size; ++i)
	{
		std::vector<int> indexes = get_neighbors(source, i);
		//std::cout << "Vertex ";
		//print(graph[i].data);
		//std::cout << ":" << std::endl;
		for (int j = 0; j < indexes.size(); ++j)
		{
			graph[i].neighbors.push_back(&graph[indexes[j]]);
			//print(graph[indexes[j]].data);
			//std::cout << " ";
		}
		//std::cout << std::endl;
	}
	std::stack < Vertex <T> *> stk;
	stk.push(&graph[start_index]);
	while (0 != stk.size())
	{
		Vertex<T> * popped = stk.top();
		stk.pop();
		if (false == popped->is_visited)
		{
			popped->is_visited = true;
			print(popped->data);
			std::cout << std::endl;
			for (int i = 0; i < popped->neighbors.size(); ++i)
			{
				stk.push(popped->neighbors[i]);
			}
		}
	}
}

template <class T> void breadth(std::vector<T> source, int start_index, std::vector<int> (* get_neighbors)(std::vector<T> arr, int index), void (*print)(T value))
{
	int size = source.size();
	std::vector< Vertex<T> > graph(size);
	for (int i = 0; i < size; ++i)
	{
		graph[i].data = source[i];
		graph[i].is_visited = false;
	}
	for (int i = 0; i < size; ++i)
	{
		std::vector<int> indexes = get_neighbors(source, i);
		for (int j = 0; j < indexes.size(); ++j)
		{
			graph[i].neighbors.push_back(&graph[indexes[j]]);
		}
	}
	std::queue < Vertex <T> *> que;
	que.push(&graph[start_index]);
	while (0 != que.size())
	{
		Vertex<T> * popped = que.front();
		que.pop();
		if (false == popped->is_visited)
		{
			popped->is_visited = true;
			print(popped->data);
			std::cout << std::endl;
			for (int i = 0; i < popped->neighbors.size(); ++i)
			{
				que.push(popped->neighbors[i]);
			}
		}
	}
}


