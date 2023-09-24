#include "Util/UnrolledLinkedList.hpp"
#include "gtest/gtest.h"

TEST(UnrolledLinkedListFindSuite, Find)
{
	UnrolledLinkedList ull;
	std::vector<int> values = {15, -7, 6, 9, 34, 80, 124};
	std::vector<int> to_find = {5, -7, 15, 34, 80};

	for (auto &value : values)
	{
		ull.push_back(value);
		std::cerr << ull.size() << ' ' << ull << '\n';
	}
	for (auto &value : to_find)
	{
		auto idx = ull.find(value);

		if (idx == -1)
		{
			std::cerr << value << " not found\n";
		}
		else
		{
			std::cerr << ull.size() << ' ' << ull << '\n';
			std::cerr << value << " found at idx " << idx;
			std::cerr << "\ncontainer value: " << ull.at(idx) << '\n';
		}
	}
}

TEST(UnrolledLinkedListFindSuite, At)
{
	UnrolledLinkedList ull;
	std::vector<int> values = {15, -7, 6, 9, 34, 55, 51231, 54, 80, 124, 141, 5145, -145, 55};

	for (auto &value : values)
	{
		ull.push_back(value);
		std::cerr << ull.size() << ' ' << ull << std::endl;
	}
	for (int i = 0; i < values.size(); ++i)
	{
		std::cerr << ull.at(i) << std::endl;
	}
}