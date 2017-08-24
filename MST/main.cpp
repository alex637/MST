#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include "DisjointSetsInt.h"
#include "heap.cpp"

#define INF 10000


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


struct Edge
{
	int u, v;
	double weight;

	bool operator<(const Edge other) const
	{
		return (weight < other.weight);
	}
};


//Writes in mst edges of minimum spanning tree of graph.
//Needs time O(E*logV). ?
void kruskal(std::vector<Edge>& graph, std::vector<Edge>& mst, int v)
{
	std::sort(graph.begin(), graph.end());
	DisjointSetsInt a(v);
	for (int i = 0; i < v; i++)
		a.make_set(i);
	for (std::vector<Edge>::iterator i = graph.begin();
		i != graph.end(); i++)
		if (a.find_set(i->u) != a.find_set(i->v))
		{
			mst.push_back(*i);
			a.unite(i->u, i->v);
		}
}


void prim(Graph& graph, int * mst_predecessors, int start = 0)
{
	int *indices = new int[graph.vertices]; //indices[v] is the index of v in the heap
	std::vector<bool> in_queue;
	in_queue.assign(graph.vertices, true);
	Heap < Graph::Node, std::greater<Graph::Node> > heap(graph.vertices, indices);


	for (int i = 0; i < graph.vertices; i++)
		if (i != start)
			heap.push(Graph::Node{ i, INF });
		else
			heap.push(Graph::Node{ i, 0 });
	mst_predecessors[start] = start; // root of the tree

	while (!heap.empty())
	{
		Graph::Node u = heap.pop();
		in_queue[u.vertex] = false;
		for (std::list<Graph::Node>::const_iterator i = graph.adj[u.vertex].begin();
			i != graph.adj[u.vertex].end(); i++)
			if (in_queue[i->vertex] && i->weight < heap.arr[indices[i->vertex]].weight)
			{
				mst_predecessors[i->vertex] = u.vertex;
				heap.arr[indices[i->vertex]].weight = i->weight;
				heap.refresh(indices[i->vertex]);
			}
	}
	delete[] indices;
}


int main()
{
	int v, e;
	std::cin >> v >> e;
	Graph graph(v, e, false);
/*
	//reading graph as list of edges
	std::vector<Edge> graph, mst;
	for (int i = 0; i < e; i++)
	{
		int v1, v2;
		double w;
		std::cin >> v1 >> v2 >> w;
		graph.push_back(Edge{ v1, v2, w });
	}

	kruskal(graph, mst, v);

	for (std::vector<Edge>::iterator i = mst.begin();
	i != mst.end(); i++)
	std::cout << i->u << " " << i->v << " " << i->weight << "\n";
*/
	int * mst_predecessors = new int[v];
	
	prim(graph, mst_predecessors);
	
	std::cout << "\nMinimum spanning tree:\n";
	for (int i = 0; i < v; i++)
		std::cout << i << " : " << mst_predecessors[i] << std::endl;

	std::cout << "\n";
	system("pause");
	return 0;
}