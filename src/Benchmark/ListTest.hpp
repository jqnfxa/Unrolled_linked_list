#include "Profiler/Timer.hpp"
#include "Random/Generator.hpp"
#include <numeric>
#include <iostream>
#include <random>
#include <vector>
#include <list>

void test_list_insert(int lim)
{
	std::cerr << lim << '\n';
	int from = -500000;
	int to = 500000;

	std::vector<int> test = Generator::gen_range(lim, from, to);

	{
		Timer timer(std::cerr, "List insert (best) (push_back)");
		std::list<int> container;

		for (int i: test)
		{
			container.push_back(i);
		}
	}
	{
		Timer timer(std::cerr, "List insert (best) (push_front)");
		std::list<int> container;

		for (int i: test)
		{
			container.push_front(i);
		}
	}
	{
		Timer timer(std::cerr, "List insert (average) (push_middle)");
		std::list<int> container;

		for (int i = 0; i < test.size() / 2; ++i)
		{
			container.push_back(test[i]);
		}
		for (int i = test.size() / 2 + 1; i < test.size(); ++i)
		{
			auto idx = Generator::pick_num(0, container.size() / 2);
			container.insert(std::next(container.begin(), idx), test[i]);
		}
	}
	{
		Timer timer(std::cerr, "List insert (worst) (push in middle)");
		std::list<int> container;
		container.push_back(test[0]);

		for (int i = 1; i < test.size(); ++i)
		{
			auto idx = Generator::pick_num(container.size() / 4, container.size() * 3 / 4);
			container.insert(std::next(container.begin(), idx), test[i]);
		}
	}
}
void test_list_erase(int lim)
{
	std::cerr << lim << '\n';
	int from = -500000;
	int to = 500000;

	std::vector<int> test = Generator::gen_range(lim, from, to);

	{
		std::list<int> container;

		for (int i: test)
		{
			container.push_back(i);
		}
		{
			Timer timer(std::cerr, "List erase (best) (pop_back)");

			while (!container.empty())
			{
				container.pop_back();
			}
		}
	}
	{
		std::list<int> container;

		for (int i: test)
		{
			container.push_back(i);
		}
		{
			Timer timer(std::cerr, "List erase (best) (pop_front)");

			while (!container.empty())
			{
				container.pop_front();
			}
		}
	}
	{
		std::list<int> container;

		for (int i: test)
		{
			container.push_back(i);
		}

		{
			Timer timer(std::cerr, "List erase (worst) (pop from middle)");

			while (!container.empty())
			{
				int pick = Generator::pick_num(container.size() / 2, container.size() * 3 / 4);
				container.erase(std::next(container.begin(), pick));
			}
		}
	}
	{
		std::list<int> container;

		for (int i: test)
		{
			container.push_back(i);
		}

		{
			Timer timer(std::cerr, "List erase (average) (pop from middle)");

			while (!container.empty())
			{
				int pick = Generator::pick_num(0, container.size() - 1);
				container.erase(std::next(container.begin(), pick));
			}
		}
	}
}
void test_list_find(int lim)
{
	std::cerr << lim << '\n';
	int from = -500000;
	int to = 500000;

	{
		std::vector<int> test(lim);
		std::iota(test.begin(), test.end(), 0);
		std::list<int> lst;

		for (auto i : test)
		{
			lst.push_back(i);
		}
		std::vector<std::list<int>::iterator> iters;
		iters.reserve(lim);

		{
			Timer timer(std::cerr, "List find (best) in sorted array");

			for (int i = 0; i < lim; ++i)
			{
				int idx = Generator::pick_num(0, lim / 4);
				iters.push_back(std::find(lst.begin(), lst.end(), idx));
			}
		}
	}
	{
		std::vector<int> test = Generator::gen_range(lim, from, to);

		std::list<int> lst;

		for (auto i : test)
		{
			lst.push_back(i);
		}

		std::vector<int> to_find = test;
		std::vector<std::list<int>::iterator> iters;
		iters.reserve(lim);
		std::shuffle(to_find.begin(), to_find.end(), std::mt19937(std::random_device()()));

		{
			Timer timer(std::cerr, "List find (average) (random)");

			for (int i: to_find)
			{
				iters.push_back(std::find(lst.begin(), lst.end(), i));
			}
		}
	}
	{
		std::vector<int> test = Generator::gen_range(lim, from, to);

		std::list<int> lst;

		for (auto i : test)
		{
			lst.push_back(i);
		}

		std::vector<int> to_find = Generator::gen_range(lim, -1000000, -700000);
		std::vector<std::list<int>::iterator> iters;
		iters.reserve(lim);

		{
			Timer timer(std::cerr, "List find (worst) (no element)");

			for (int i: to_find)
			{
				iters.push_back(std::find(lst.begin(), lst.end(), i));
			}
		}
	}
}

void benchmark_list(int small, int medium, int big)
{
	test_list_insert(small);
	test_list_insert(medium);
	test_list_insert(big);

	test_list_erase(small);
	test_list_erase(medium);
	test_list_erase(big);

	test_list_find(small);
	test_list_find(medium);
	test_list_find(big);
}