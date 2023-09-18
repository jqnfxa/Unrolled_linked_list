#include "Node.hpp"

Node::Node(int maxElements, Node *previous, Node *next) : size(0), next(next), prev(previous), elements(maxElements)
{
	if (previous != nullptr)
	{
		previous->next = this;
	}
	if (next != nullptr)
	{
		next->prev = this;
	}
}