#include "UnrolledLinkedList.hpp"

UnrolledLinkedList::UnrolledLinkedList(int n_array) : capacity(n_array),
													  half_full((capacity + 1) / 2),
													  size_(0),
													  head(nullptr),
													  tail(nullptr)
{
	if (n_array < 2)
	{
		throw std::invalid_argument(std::to_string(n_array) + " is invalid size of node array");
	}
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
void UnrolledLinkedList::insert(int absolute_index, int value)
{
	if (absolute_index == 0)
	{
		push_front(value);
		return;
	}
	else if (absolute_index == size_)
	{
		push_back(value);
		return;
	}

	auto [node, relative_index] = get_relative_index(absolute_index);

	if (node == nullptr)
	{
		return;
	}

	insert_in_node(node, relative_index, value);
}
void UnrolledLinkedList::push_back(int value)
{
	if (head == nullptr)
	{
		head = new Node(capacity);
		tail = head;
	}

	insert_in_node(tail, tail->size, value);
}
void UnrolledLinkedList::push_front(int value)
{
	if (head == nullptr)
	{
		head = new Node(capacity);
		tail = head;
	}

	insert_in_node(head, 0, value);
}
void UnrolledLinkedList::pop_back()
{
	if (tail == nullptr)
	{
		return;
	}

	erase_from_node(tail, tail->size - 1);
	balance(tail);
}
void UnrolledLinkedList::pop_front()
{
	if (head == nullptr)
	{
		return;
	}

	erase_from_node(head, 0);
	balance(head);
}
void UnrolledLinkedList::erase(int absolute_index)
{
	auto [node, idx] = get_relative_index(absolute_index);

	// means invalid index
	if (node == nullptr)
	{
		return;
	}

	erase_from_node(node, idx);
	balance(node);
}
void UnrolledLinkedList::erase_by_value(int value)
{
	erase(find(value));
}
void UnrolledLinkedList::balance(Node *node)
{
	if (node == nullptr)
	{
		return;
	}
	// have enough elements
	if (node->size >= half_full)
	{
		return;
	}
	// next node is null so no elements can be moved
	if (node->next == nullptr)
	{
		if (node->empty())
		{
			erase_node(node);
		}
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
		if (prev == nullptr && next == nullptr)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else if (prev == nullptr)
		{
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		else
		{
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
	}
	else
	{
		prev->next = next;
		next->prev = prev;

		delete node;
	}
}
std::ostream &operator<<(std::ostream &out, const UnrolledLinkedList &unrolled_linked_list)
{
	auto *node = unrolled_linked_list.head;

	while (node != nullptr)
	{
		out << "[";
		for (int i = 0; i < node->size; ++i)
		{
			out << node->elements[i];

			if (i != node->size - 1)
			{
				out << ", ";
			}
		}
		out << "]";
		if (node->next != nullptr)
		{
			out << " -> ";
		}
		node = node->next;
	}
	return out;
}
std::pair<Node *, int> UnrolledLinkedList::get_relative_index(int index) const
{
	Node *node = nullptr;
	int related_idx = -1;

	if (index == size())
	{
		node = tail;
		related_idx = tail == nullptr ? -1 : tail->size;
	}
	else if (index >= 0 && index < size())
	{
		int half = size() / 2;
		int first = index < half;

		auto *temp = first ? head : tail;
		int node_start = first ? 0 : size() - tail->size;
		int max_index;
		bool condition;

		while (temp != nullptr)
		{
			max_index = node_start + temp->size - 1;
			condition = first ? max_index < index : node_start > index;

			if (condition)
			{
				node_start += first ? temp->size : -temp->prev->size;
				temp = first ? temp->next : temp->prev;
			}
			else
			{
				break;
			}
		}

		node = temp;
		related_idx = index - node_start;
	}
	return {node, related_idx};
}
void UnrolledLinkedList::insert_in_node(Node *node, int relative_index, int value)
{
	if (node == nullptr || relative_index < 0 || relative_index > capacity)
	{
		return;
	}

	// balance node
	if (node->is_full())
	{
		node = node->insert_node(node);

		if (tail == node)
		{
			tail = node->next;
		}
	}
	if (relative_index > node->size)
	{
		insert_in_node(node->next, relative_index - node->size, value);
		return;
	}

	for (int i = node->size; i > relative_index; i--)
	{
		node->elements[i] = node->elements[i - 1];
	}
	node->elements[relative_index] = value;
	node->size++;
	size_++;
}
int UnrolledLinkedList::size() const
{
	return size_;
}
bool UnrolledLinkedList::empty() const
{
	return size() == 0;
}
int UnrolledLinkedList::at(int absolute_index) const
{
	if (absolute_index < 0 || absolute_index >= size_)
	{
		throw std::out_of_range(
			"Addressing by index [" + std::to_string(absolute_index) + "], but container have " + std::to_string(size_)
			+ " elements");
	}
	auto [node, idx] = get_relative_index(absolute_index);
	return node->elements[idx];
}
int UnrolledLinkedList::find(int value) const
{
	auto *node = head;
	int index = 0;
	bool found = false;

	while (node != nullptr && !found)
	{
		for (int i = 0; i < node->size; ++i)
		{
			if (node->elements[i] == value)
			{
				index += i;
				found = true;
				break;
			}
		}
		if (!found)
		{
			index += node->size;
			node = node->next;
		}
	}
	return found ? index : -1;
}
void UnrolledLinkedList::erase_from_node(Node *node, int idx)
{
	if (node == nullptr || idx < 0 || idx >= node->size)
	{
		return;
	}

	std::copy(node->elements.begin() + idx + 1, node->elements.begin() + node->size, node->elements.begin() + idx);
	node->size--;
	size_--;
}
std::ostream &UnrolledLinkedList::print_raw(std::ostream &out, const std::string &sep, const std::string &end) const
{
	auto *node = head;

	while (node != nullptr)
	{
		for (int i = 0; i < node->size; ++i)
		{
			out << node->elements[i];

			if (i != node->size - 1)
			{
				out << sep;
			}
		}
		node = node->next;
	}
	return out << end;
}
