#include <iostream>
#include <vector>
#include <list>
#include "DisjointSetsInt.h"


class Graph
{
public:
	struct Node
	{
		int vertex;
		double weight;

		bool operator<(const Node x) const
		{
			return weight < x.weight;
		}

		bool operator>(const Node x) const
		{
			return weight > x.weight;
		}

		bool operator==(Node x)
		{
			if (vertex == x.vertex && weight == x.weight)
				return true;
			else
				return false;
		}
	};

	int vertices, edges;
	std::vector<std::list<Node>> adj;
	bool digraph;

	//Constructor, reads edges with weights
	Graph(int v, int e, bool orgraph)
	{
		vertices = v;
		edges = e;
		digraph = orgraph;
		for (int i = 0; i < v; i++)
		{
			std::list<Node> a;
			adj.push_back(a);
		}
		for (int i = 0; i < e; i++)
		{
			int v1, v2;
			double w;
			std::cin >> v1 >> v2 >> w;
			adj[v1].push_back(Node{ v2, w });
			if (!digraph)
				adj[v2].push_back(Node{ v1, w });
		}
	}
};


int main()
{
	int v, e;
	std::cin >> v >> e;
	Graph graph(v, e, false);



	system("pause");
	return 0;
}