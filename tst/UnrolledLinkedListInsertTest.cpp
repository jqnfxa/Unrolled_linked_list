#include <UnrolledLinkedList.hpp>
#include "gtest/gtest.h"

TEST(UnrolledLinkedListInsertSuite, PushBack)
{
	UnrolledLinkedList ull;

	ull.push_back(15);
	std::cerr << ull << '\n';
	ull.push_back(14);
	std::cerr << ull << '\n';
	ull.push_back(6);
	std::cerr << ull << '\n';
	ull.push_back(10);
	std::cerr << ull << '\n';
	ull.push_back(4);
	std::cerr << ull << '\n';
}

TEST(UnrolledLinkedListInsertSuite, PushFront)
{
	UnrolledLinkedList ull;

	ull.push_back(14);
	ull.push_back(6);
	std::cerr << ull << '\n';

	ull.push_front(15);
	std::cerr << ull << '\n';
	ull.push_front(1);
	std::cerr << ull << '\n';
	ull.push_front(7);
	std::cerr << ull << '\n';
}

TEST(UnrolledLinkedListInsertSuite, InsertGeneral)
{
	UnrolledLinkedList ull;

	ull.push_back(15);
	ull.push_back(-7);
	std::cerr << ull << '\n';

	ull.insert(1, 6);
	std::cerr << ull << '\n';
	ull.insert(2, 4);
	std::cerr << ull << '\n';
	ull.push_front(6);
	std::cerr << ull << '\n';
	std::cerr << ull.find(6);
}