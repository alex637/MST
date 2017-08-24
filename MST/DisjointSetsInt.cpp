#include "DisjointSetsInt.h"


DisjointSetsInt::DisjointSetsInt(int number_of_elements = MAXNUMBEROFELEM)
{
	//Allocates memory!
	capasity = number_of_elements;
	Node ** addr = new Node *[capasity];
	addresses = addr;
	n = 0;
}

DisjointSetsInt::~DisjointSetsInt()
{
	for (int i = 0; i < n; i++)
		delete addresses[i];
	delete addresses;
}


void DisjointSetsInt::make_set(int x)
{
	Root * ptr = new Root(x);
	ptr->p = ptr;
	if (x >= capasity)
		return;
	addresses[x] = ptr;
	n++;
}


void DisjointSetsInt::unite(int x, int y)
{
	n--;
	Root * p1 = (Root*)_find_set(addresses[x]);
	Root * p2 = (Root*)_find_set(addresses[y]);
	if (p1->rank > p2->rank)
	{
		Node * ptr = new Node(p2->value);
		ptr->p = p1;
		addresses[y] = ptr;
		delete p2;
	}
	else
	{
		Node * ptr = new Node(p1->value);
		ptr->p = p2;
		addresses[x] = ptr;
		if (p1->rank == p2->rank)
			p2->rank++;
		delete p1;
	}
}


int DisjointSetsInt::find_set(int x)
{
	return _find_set(addresses[x])->value;
}

DisjointSetsInt::Node * DisjointSetsInt::_find_set(Node * ptr)
{
	if (ptr != ptr->p)
		ptr->p = _find_set(ptr->p);
	return ptr->p;
}


int DisjointSetsInt::number_of_components()
{
	return n;
}
