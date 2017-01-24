#include <iostream>
#include <vector>
#include <stack>
#include <queue>

template <class VertexType> struct Vertex {
	std::vector< Vertex <VertexType> * > neighbors;
	VertexType data;
	bool is_visited;	
};

template <class VertexType, class GraphType, class NeighborFunction, class PrintFunction> class Graph {
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
		Vertex <VertexType>& getVertex(VertexType data)
		{
			for (int i = 0; i < vertexes.size(); ++i)
			{
				if (vertexes[i].data == data)
				{
					return vertexes[i];
				}
			}
			throw -1;
		}
		Vertex <VertexType>& operator[](int index)
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
        		Vertex<VertexType>& new_neighbor = getVertex(to_add);
				vertexes[index].neighbors.push_back(&new_neighbor);
			}
		}
		void fillGraph(GraphType source)
		{
			for (auto src : source) // adding vertexes from container
			{
				Vertex<VertexType> to_add;
				to_add.data = src;
				to_add.is_visited = false;
				addVertex(to_add);
			}
		}
		void fillNeighbors(GraphType source, NeighborFunction get_neighbors)
		{
			for (int i = 0; i < vertexes.size(); ++i) // adding neighbors
			{
				auto indexes = get_neighbors(source, vertexes[i].data);
				for (auto j : indexes)
				{
					addNeighbor(i, j);
				}
			}
		}
		void printGraph(PrintFunction print)
		{
			for (int i = 0; i < vertexes.size(); ++i)
			{
				std::cout << "Vertex " << i << std::endl;
				Vertex < VertexType > vertex = vertexes[i];
				print(vertex.data);
				std::cout << std::endl << "Neighbors: " << std::endl;
				for (int j = 0; j < vertex.neighbors.size(); ++j)
				{
					print(vertex.neighbors[j]->data); 
				}
				std::cout << std::endl << std::endl;;
			}
		}
	private:
		std::vector< Vertex<VertexType> > vertexes;
};


template <class VertexType, class GraphType, class NeighborFunction, class PrintFunction> 
void depth(VertexType start_index, GraphType source, NeighborFunction get_neighbors, PrintFunction print) 
{
	std::cout << "DFS" << std::endl;
	Graph<VertexType, GraphType, NeighborFunction, PrintFunction> graph;
	graph.fillGraph(source);
	graph.fillNeighbors(source, get_neighbors);
	//graph.printGraph(print);
	std::stack < Vertex <VertexType> *> stk; 
	stk.push(&graph.getVertex(start_index));
	while (!stk.empty())
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
	}
	std::cout << std::endl << std::endl;
}

template <class VertexType, class GraphType, class NeighborFunction, class PrintFunction> 
void breadth(VertexType start_index, GraphType source, NeighborFunction get_neighbors, PrintFunction print) 
{
	std::cout << "BFS" << std::endl;
	Graph<VertexType, GraphType, NeighborFunction, PrintFunction> graph;
	graph.fillGraph(source);
	graph.fillNeighbors(source, get_neighbors);
	//graph.printGraph(print);
	std::queue < Vertex <VertexType> *> que; 
	que.push(&graph.getVertex(start_index));
	while (!que.empty())
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
	std::cout << std::endl << std::endl;
}


