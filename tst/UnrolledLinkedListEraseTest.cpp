#include <UnrolledLinkedList.hpp>
#include <random>
#include "gtest/gtest.h"

TEST(UnrolledLinkedListEraseSuite, PopBack)
{
	UnrolledLinkedList ull;
	std::vector<int> values = {15, -7, 6, 9, 34, 80, 124};

	for (auto &value : values)
	{
		ull.push_back(value);
		std::cerr << ull.size() << ' ' << ull << '\n';
	}

	while (!ull.empty())
	{
		ull.pop_back();
		std::cerr << ull.size() << ' ' << ull << '\n';
	}
}

TEST(UnrolledLinkedListEraseSuite, PopFront)
{
	UnrolledLinkedList ull;
	std::vector<int> values = {15, -7, 6, 9, 34, 80, 124};

	for (auto &value : values)
	{
		ull.push_back(value);
		std::cerr << ull.size() << ' ' << ull << '\n';
	}

	while (!ull.empty())
	{
		ull.pop_front();
		std::cerr << ull.size() << ' ' << ull << '\n';
	}
}

TEST(UnrolledLinkedListEraseSuite, EraseByIndex)
{
	UnrolledLinkedList ull;
	std::vector<int> values = {15, -7, 6, 9, 34, 80, 124};

	for (auto &value : values)
	{
		ull.push_back(value);
		std::cerr << ull << '\n';
	}

	ull.erase(3);
	std::cerr << ull << '\n';
	ull.erase(4);
	std::cerr << ull << '\n';
	ull.erase(-1);
	std::cerr << ull << '\n';
	ull.erase(7);
	std::cerr << ull << '\n';
	ull.erase(1);
	std::cerr << ull << '\n';
}

TEST(UnrolledLinkedListEraseSuite, EraseByValue)
{
	UnrolledLinkedList ull;
	std::vector<int> values = {15, -7, 6, 9, 34, 80, 124, 34241};

	for (auto &value : values)
	{
		ull.push_back(value);
		std::cerr << ull.size() << ' ' << ull << '\n';
	}
	std::shuffle(values.begin(), values.end(), std::mt19937(std::random_device()()));

	for (auto &value : values)
	{
		ull.erase_by_value(value);
		std::cerr << ull.size() << ' ' << ull << '\n';
	}
}

TEST(UnrolledLinkedListEraseSuite, Tst)
{
	UnrolledLinkedList ull;
	std::vector<int> values = {12,16,15};

	for (auto &value : values)
	{
		ull.push_back(value);
		std::cerr << ull.size() << ' ' << ull << '\n';
	}
	ull.insert(2, 228);
	std::cerr << ull.size() << ' ' << ull << '\n';
	ull.push_back(282);
	std::cerr << ull.size() << ' ' << ull << '\n';
	ull.erase_by_value(16);
	std::cerr << ull.size() << ' ' << ull << '\n';
	ull.push_back(12);
	std::cerr << ull.size() << ' ' << ull << '\n';
	ull.erase_by_value(12);
	std::cerr << ull.size() << ' ' << ull << '\n';
	ull.erase(1);
	std::cerr << ull.size() << ' ' << ull << '\n';
}