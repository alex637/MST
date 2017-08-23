#pragma once

#define MAXNUMBEROFELEM 10000


class DisjointSetsInt
{
	class Node
	{
	public:
		int value;
		Node * p = nullptr; //predecessor or root if compressing paths

		Node(int x)
		{
			value = x;
		}
	};

	class Root :public Node
	{
	public:
		int rank;
		
		Root(int x) :
			Node(x)
		{
			rank = 0;
		}
	};

	Node ** addresses;
	int capasity; //maximum number of disjoint sets of integer
	int n; //real number of disjoint sets of integer

public:
	DisjointSetsInt(int number_of_elements);

	~DisjointSetsInt();

	void make_set(int x);

	void unite(int x, int y);

	int find_set(int x);

	int number_of_components();

private:

	Node * _find_set(Node *);
};