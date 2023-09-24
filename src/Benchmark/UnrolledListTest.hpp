#include "Profiler/Timer.hpp"
#include "Random/Generator.hpp"
#include "Util/UnrolledLinkedList.hpp"
#include <numeric>
#include <iostream>
#include <random>
#include <vector>

void test_unrolled_insert(int lim, int cache)
{
	std::cerr << lim << '\n';
	int from = -500000;
	int to = 500000;

	std::vector<int> test = Generator::gen_range(lim, from, to);

	{
		Timer timer(std::cerr, "Unrolled list insert (best) (push_back)");
		UnrolledLinkedList container(cache);

		for (int i: test)
		{
			container.push_back(i);
		}
	}
	{
		Timer timer(std::cerr, "Unrolled list insert (average) (push_mid)");
		UnrolledLinkedList container(cache);

		for (int i = 0; i < test.size() / 2; ++i)
		{
			container.push_back(test[i]);
		}
		for (int i = test.size() / 2 + 1; i < test.size(); ++i)
		{
			container.insert(Generator::pick_num(0, container.size() - 1), test[i]);
		}
	}
	{
		Timer timer(std::cerr, "Unrolled insert (best) (push_front)");
		UnrolledLinkedList container(cache);

		for (int i: test)
		{
			container.push_front(i);
		}
	}
}
void test_unrolled_erase(int lim, int cache)
{
	std::cerr << lim << '\n';
	int from = -500000;
	int to = 500000;

	std::vector<int> test = Generator::gen_range(lim, from, to);

	{
		UnrolledLinkedList container(cache);

		for (auto &item : test)
		{
			container.push_back(item);
		}

		{
			Timer timer(std::cerr, "Unrolled erase (best) (pop_back)");
			while (!container.empty())
			{
				container.pop_back();
			}
		}
	}
	{
		UnrolledLinkedList container(cache);

		for (auto &item : test)
		{
			container.push_back(item);
		}

		{
			Timer timer(std::cerr, "Unrolled erase (best) (pop_front)");
			while (!container.empty())
			{
				container.pop_front();
			}
		}
	}
	{
		UnrolledLinkedList container(cache);

		for (auto &item : test)
		{
			container.push_back(item);
		}

		{
			Timer timer(std::cerr, "Unrolled erase (average) (pop_from middle)");
			while (!container.empty())
			{
				container.erase(Generator::pick_num(0, container.size() - 1));
			}
		}
	}
}
void test_unrolled_find(int lim, int cache)
{
	std::cerr << lim << '\n';
	int from = -500000;
	int to = 500000;
	{
		std::vector<int> test(lim);
		std::iota(test.begin(), test.end(), 0);
		UnrolledLinkedList container(cache);
		std::vector<int> iters;
		iters.reserve(lim);

		for (auto &item : test)
		{
			container.push_back(item);
		}

		{
			Timer timer(std::cerr, "Unrolled find (best) in sorted array");

			for (int i = 0; i < lim; ++i)
			{
				int idx = Generator::pick_num(0, lim / 4);
				iters.push_back(container.find(idx));
			}
		}
	}
	{
		std::vector<int> test = Generator::gen_range(lim, from, to);
		std::vector<int> to_find = test;

		UnrolledLinkedList container(cache);
		std::vector<int> iters;
		iters.reserve(lim);

		for (auto &item : test)
		{
			container.push_back(item);
		}

		std::shuffle(to_find.begin(), to_find.end(), std::mt19937(std::random_device()()));

		{
			Timer timer(std::cerr, "Unrolled find (average) (random)");

			for (int i: to_find)
			{
				iters.push_back(container.find(i));
			}
		}
	}
	{
		std::vector<int> test = Generator::gen_range(lim, from, to);

		UnrolledLinkedList container(cache);
		std::vector<int> iters;
		iters.reserve(lim);

		for (auto &item : test)
		{
			container.push_back(item);
		}

		{
			Timer timer(std::cerr, "Unrolled find (worst) (no element)");

			for (int i = 0; i < test.size(); ++i)
			{
				iters.push_back(container.find(-7000009));
			}
		}
	}
	{
		std::vector<int> test = Generator::gen_range(lim, from, to);

		UnrolledLinkedList container(cache);
		std::vector<int> iters;
		iters.reserve(lim);

		for (auto &item : test)
		{
			container.push_back(item);
		}

		{
			Timer timer(std::cerr, "Addressing");

			for (int i = 0; i < test.size(); ++i)
			{
				iters.push_back(container.at(i));
			}
		}
	}
}

void benchmark_unrolled_list(int small, int medium, int big, int cache)
{
	test_unrolled_insert(small, cache);
	test_unrolled_insert(medium, cache);
	test_unrolled_insert(big, cache);

	test_unrolled_erase(small, cache);
	test_unrolled_erase(medium, cache);
	test_unrolled_erase(big, cache);

	test_unrolled_find(small, cache);
	test_unrolled_find(medium, cache);
	test_unrolled_find(big, cache);
}