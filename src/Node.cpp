#include "Node.hpp"

Node::Node(int max_elements, Node *previous, Node *next) : size(0), next(next), prev(previous), elements(max_elements)
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
Node *Node::insert_node(Node *old)
{
	if (old == nullptr)
	{
		return nullptr;
	}

	// if node is full then create new node
	int capacity = static_cast<int>(old->elements.size());
	int mid = (capacity + 1) / 2;
	auto *new_node = new Node(static_cast<int>(old->elements.size()), old, old->next);

	// copy right half
	std::copy(old->elements.begin() + mid, old->elements.end(), new_node->elements.begin());
	new_node->size = capacity - mid;
	old->size = mid;

	return old;
}
bool Node::is_full() const
{
	return size == elements.size();
}
bool Node::empty() const
{
	return size == 0;
}
