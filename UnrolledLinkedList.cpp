#include "UnrolledLinkedList.hpp"

UnrolledLinkedList::UnrolledLinkedList(int n_array) : capacity(n_array), head(nullptr), tail(nullptr)
{
}
void UnrolledLinkedList::insert_in_node(Node *node, int value)
{
	if (node == nullptr)
	{
		return;
	}
	int index = 0;

	while (index < node->size && node->elements[index] < value)
	{
		index++;
	}

	// value strictly greater than all values (add to end)
	if (index == node->size)
	{
		// have we enough space?
		if (node->size < capacity)
		{
			node->elements[node->size++] = value;
		}
			// if node is full then create new node
		else
		{
			int mid = capacity / 2;
			auto *new_node = new Node(capacity, node, node->next);
			std::copy(node->elements.begin() + mid, node->elements.end(), new_node->elements.begin());
			node->size = mid;
			new_node->size = capacity - mid;
			new_node->elements[new_node->size++] = value;

			// update tail
			if (node == tail)
			{
				tail = new_node;
			}
		}
	}
		// value should be added in the middle
	else
	{
		// we have enough space to store value
		if (node->size + 1 <= capacity)
		{
			for (int i = node->size; i > index; i--)
			{
				node->elements[i] = node->elements[i - 1];
			}
			node->elements[index] = value;
			node->size++;
		}
		else
		{
			int mid = capacity / 2;
			auto *new_node = new Node(capacity, node, node->next);
			std::copy(node->elements.begin() + mid, node->elements.end(), new_node->elements.begin());
			node->size = mid;
			new_node->size = capacity - mid;

			// update tail
			if (node == tail)
			{
				tail = new_node;
			}

			if (node->elements[node->size - 1] <= value && new_node->elements[0] >= value)
			{
				node->elements[node->size++] = value;
			}
			else
			{
				insert_in_node(new_node, value);
			}
		}
	}
}
void UnrolledLinkedList::insert(int value)
{
	insert_in_node(find_node_to_insert(value), value);
}
Node *UnrolledLinkedList::find_node_to_insert(int value)
{
	Node *node_to_insert = nullptr;

	if (head == nullptr)
	{
		head = new Node(capacity);
		tail = head;
		node_to_insert = tail;
	}
	else
	{
		auto *node = head;

		/*
		 * find node which have elements[0] > value,
		 * so we need to insert value in previous node
		 * If previous node is nullptr then insert to current node (head)
		 */

		while (node != nullptr && node->elements[0] <= value)
		{
			node = node->next;
		}

		// we should add element in last node
		if (node == nullptr)
		{
			node_to_insert = tail;
		}
		else if (node->prev == nullptr)
		{
			node_to_insert = head;
		}
		else
		{
			node_to_insert = node->prev;
		}
	}
	return node_to_insert;
}
void UnrolledLinkedList::erase(int value)
{
	auto [node, idx] = find(value);

	// means element not found
	if (node == nullptr)
	{
		return;
	}

	for (int i = idx; i < capacity - 1; ++i)
	{
		node->elements[i] = node->elements[i + 1];
	}
	node->size--;
	balance(node);
}
std::pair<Node *, int> UnrolledLinkedList::find(int value) const
{
	Node *node = head;

	while (node != nullptr)
	{
		for (int i = 0; i < node->size; ++i)
		{
			if (node->elements[i] == value)
			{
				return {node, i};
			}
		}

		node = node->next;
	}
	return {nullptr, -1};
}
void UnrolledLinkedList::balance(Node *node)
{
	if (node == nullptr)
	{
		return;
	}
	int half_full = (capacity + 1) / 2;

	// have enough elements
	if (node->size >= half_full)
	{
		return;
	}
	// next node is null so no elements can be moved
	if (node->next == nullptr)
	{
		return;
	}

	int elems_required = half_full - node->size;

	// capture all elements if next node have not enough elements
	if (node->next->size - elems_required < half_full)
	{
		std::copy(node->next->elements.begin(),
				  node->next->elements.begin() + node->next->size, node->elements.begin() + node->size);
		node->size += node->next->size;
		node->next->size = 0;
		erase_node(node->next);
	}
	else
	{
		std::copy(node->next->elements.begin(),
				  node->next->elements.begin() + elems_required, node->elements.begin() + node->size);
		node->size += elems_required;
		node->next->size -= elems_required;

		for (int j = elems_required; j < capacity; ++j)
		{
			node->next->elements[j - elems_required] = node->next->elements[j];
		}
	}
}
void UnrolledLinkedList::erase_node(Node *node)
{
	if (node == nullptr)
	{
		return;
	}

	auto *prev = node->prev;
	auto *next = node->next;

	// delete of edge nodes
	if (prev == nullptr || next == nullptr)
	{
		// only head left
		if (prev == nullptr && next == nullptr)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		// delete of head node
		else if (prev == nullptr)
		{
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		// delete tail node
		else
		{
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
	}
	// delete node from the middle
	else
	{
		prev->next = next;
		next->prev = prev;

		delete node;
	}
}
std::ostream &operator<<(std::ostream &out, const UnrolledLinkedList &ulst)
{
	auto *node = ulst.head;

	while (node != nullptr)
	{
		out << "[";
		for (int i = 0; i < node->size; ++i)
		{
			out << node->elements[i];

			if (i != node->size - 1)
			{
				out  << ", ";
			}
		}
		out << "]";
		if (node->next != nullptr)
		{
			out << " -> ";
		}
		node = node->next;
	}
	return out << std::endl;
}
UnrolledLinkedList::~UnrolledLinkedList()
{
	Node *node = head;

	while (node != nullptr && node->next != nullptr)
	{
		node = node->next;
		delete node->prev;
	}
	delete node;
	head = nullptr;
	tail = nullptr;
}
