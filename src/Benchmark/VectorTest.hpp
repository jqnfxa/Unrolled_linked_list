#include "Profiler/Timer.hpp"
#include "Random/Generator.hpp"
#include <numeric>
#include <iostream>
#include <random>
#include <vector>

void test_vector_insert(int lim)
{
	std::cerr << lim << std::endl;
	int from = -500000;
	int to = 500000;

	std::vector<int> test = Generator::gen_range(lim, from, to);

	{
		std::vector<int> container;

		for (int i = 0; i < test.size() / 2; ++i)
		{
			container.push_back(test[i]);
		}

		{
			Timer timer(std::cerr, "Vector insert (average) (push_mid)");
			for (int i = test.size() / 2 + 1; i < test.size(); ++i)
			{
				auto it = container.begin() + Generator::pick_num(0, container.size() - 1);
				container.insert(it, test[i]);
			}
		}
	}
	{
		Timer timer(std::cerr, "Vector insert (worst) (push_front)");
		std::vector<int> container;

		for (int i: test)
		{
			container.insert(container.begin(), i);
		}
	}
	{
		Timer timer(std::cerr, "Vector insert (best) (push_back)");
		std::vector<int> container;

		for (int i: test)
		{
			container.push_back(i);
		}
	}
}
void test_vector_erase(int lim)
{
	std::cerr << lim << '\n';
	int from = -500000;
	int to = 500000;

	std::vector<int> test = Generator::gen_range(lim, from, to);

	{
		std::vector<int> container = test;

		{
			Timer timer(std::cerr, "Vector erase (best) (pop_back)");
			while (!container.empty())
			{
				container.pop_back();
			}
		}
	}
	{
		std::vector<int> container = test;

		{
			Timer timer(std::cerr, "Vector erase (worst) (pop_front)");
			while (!container.empty())
			{
				container.erase(container.begin());
			}
		}
	}
	{
		std::vector<int> container = test;
		{
			Timer timer(std::cerr, "Vector erase (average) (pop_from middle)");

			while (!container.empty())
			{
				auto it = container.begin() + Generator::pick_num(0, container.size() - 1);
				container.erase(it);
			}
		}
	}
}
void test_vector_find(int lim)
{
	std::cerr << lim << '\n';
	int from = -500000;
	int to = 500000;
	{
		std::vector<int> test(lim);
		std::iota(test.begin(), test.end(), 0);
		std::vector<std::vector<int>::iterator> iters;
		iters.reserve(lim);

		{
			Timer timer(std::cerr, "Vector find (best)");

			for (int i = 0; i < lim; ++i)
			{
				int idx = Generator::pick_num(0, lim / 4);
				iters.push_back(std::find(test.begin(), test.end(), idx));
			}
		}
	}
	{
		std::vector<int> test = Generator::gen_range(lim, from, to);
		std::vector<int> to_find = test;
		std::vector<std::vector<int>::iterator> iters;
		iters.reserve(lim);
		std::shuffle(to_find.begin(), to_find.end(), std::mt19937(std::random_device()()));

		{
			Timer timer(std::cerr, "Vector find (average) (random)");

			for (int i: to_find)
			{
				iters.push_back(std::find(test.begin(), test.end(), i));
			}
		}
	}
	{
		std::vector<int> test = Generator::gen_range(lim, from, to);
		std::vector<int> to_find = Generator::gen_range(lim, -1000000, -700000);
		std::vector<std::vector<int>::iterator> iters;
		iters.reserve(lim);

		{
			Timer timer(std::cerr, "Vector find (worst) (no values)");

			for (int i: to_find)
			{
				iters.push_back(std::find(test.begin(), test.end(), i));
			}
		}
	}
	{
		std::vector<int> test = Generator::gen_range(lim, from, to);
		std::vector<int> iters;
		iters.reserve(lim);

		{
			Timer timer(std::cerr, "Addressing");

			for (int i = 0; i < test.size(); ++i)
			{
				iters.push_back(test[i]);
			}
		}
	}
}

void benchmark_vector(int small, int medium, int big)
{
	test_vector_insert(small);
	test_vector_insert(medium);
	test_vector_insert(big);

	test_vector_erase(small);
	test_vector_erase(medium);
	test_vector_erase(big);

	test_vector_find(small);
	test_vector_find(medium);
	test_vector_find(big);
}