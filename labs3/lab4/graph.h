#include <iostream>
#include <vector>
#include <stack>
#include <queue>

template <class VertexType> struct Vertex {
	//Vertex(VertexType new_data) : data(new_data), is_visited(false) {}
	//~Vertex() {}
	


	std::vector< Vertex <VertexType> * > neighbors;
	VertexType data;
	bool is_visited;	
};

template <class VertexType> class Graph {
	public:
		
		
		Graph() {}
		~Graph() {}
		int size()
		{
			return vertexes.size();
		}
		bool findVertex(VertexType data)
		{
			for (int i = 0; i < vertexes.size(); ++i)
			{
				if (vertexes[i].data == data)
					return true;
			}
			return false;
		}
		void addVertex(Vertex<VertexType>& to_add)
		{
			if (!findVertex(to_add.data))
			{
				vertexes.push_back(to_add);
			}
		}
		Vertex <VertexType>& getVertexPtr(VertexType data)
		{
			for (int i = 0; i < vertexes.size(); ++i)
			{
				if (vertexes[i].data == data)
				{
					return vertexes[i];
				}
			}
			//return nullptr;
		}
		Vertex <VertexType> operator[](int index)
		{
			if ((index >= 0) && (index < vertexes.size()))
			{
				return vertexes[index];
			}
			else
			{
				throw -1;
			}
		}
		void addNeighbor(int index, VertexType to_add)
		{
			if (findVertex(to_add))
			{
				for (auto j : vertexes[index].neighbors) 
				{
        		    if ((*j).data == to_add) 
        		    {
        		        return;
        		    }
        		}
        		Vertex<VertexType>& new_neighbor = getVertexPtr(to_add);
				vertexes[index].neighbors.push_back(&new_neighbor);
				//std::cout << "ADDED " << to_add << std::endl;
				//std::cout << "SIZE NOW " << neighbors.size() << std::endl;
			}
		}


		std::vector< Vertex<VertexType> > vertexes;



	private:
		

};


template <class VertexType, class GraphType, class NeighborFunction, class PrintFunction> 
void depth(VertexType start_index, GraphType source, NeighborFunction get_neighbors, PrintFunction print) //std::vector<VertexType> ---> зашаблонить
{
	Graph<VertexType> graph;
	
	for (auto src : source) // adding vertexes from container
	{
		Vertex<VertexType> to_add;
		to_add.data = src;
		to_add.is_visited = false;
		graph.addVertex(to_add);
	}

	int size = graph.size();
	for (int i = 0; i < size; ++i)
	{
		//std::cout << " CHJBJHB " << i << std::endl; 
		auto indexes = get_neighbors(source, i);
		//std::cout << i << " check " << indexes[0] << std::endl;
		//std::cout << "Vertex ";
		//print(graph[i].data);
		//std::cout << ":" << std::endl;
		for (auto j : indexes)
		{
			
			graph.addNeighbor(i, j);
			//print(graph[indexes[j]].data);
			//std::cout << " ";
		}
		//std::cout << std::endl;
	}
	//std::cout << graph[0].neighbors.size() << " CHECK";
	for (int i = 0; i < graph.size(); ++i)
	{
		std::cout << "Vertex " << i << std::endl;
		Vertex < VertexType > vertex = graph[i];
		print(vertex.data);
		std::cout << std::endl << "Neighbors: " << std::endl;
		for (int j = 0; j < vertex.neighbors.size(); ++j)
		{
			print(vertex.neighbors[j]->data);
			std::cout << std::endl << std::endl; 
		}
	}/*
	std::stack < Vertex <VertexType> *> stk;
	stk.push(&graph[start_index]);
	while (0 != stk.size())
	{
		Vertex<VertexType> * popped = stk.top();
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
	}*/
}

/*template <class VertexType, class NeighborFunction, class PrintFunction> 
void breadth(std::vector<VertexType> source, int start_index, NeighborFunction get_neighbors, PrintFunction print)
{
	int size = source.size();
	std::vector< Vertex<VertexType> > graph(size);
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
	std::queue < Vertex <VertexType> *> que;
	que.push(&graph[start_index]);
	while (0 != que.size())
	{
		Vertex<VertexType> * popped = que.front();
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
}*/


