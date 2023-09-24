#include "Profiler/Timer.hpp"
#include "Random/Generator.hpp"
#include "Util/UnrolledLinkedList.hpp"
#include "Benchmark/UnrolledListTest.hpp"
#include <list>

void check(std::vector<int> &arr_1, std::vector<int> &arr_2, int n_array = 4)
{
	auto total_elements = std::to_string(arr_1.size());
	auto search_elements = std::to_string(arr_2.size());

	{
		UnrolledLinkedList container(n_array);
		auto message = "Insert " + total_elements + " elements (push_back) [best]";

		Timer timer(std::cerr, message);
		for (auto &item: arr_1)
		{
			container.push_back(item);
		}
	}
	{
		UnrolledLinkedList container(n_array);
		auto message = "Insert " + total_elements + " elements (push_front) [worst]";

		Timer timer(std::cerr, message);
		for (auto &item: arr_1)
		{
			container.push_front(item);
		}
	}
	{
		UnrolledLinkedList container(n_array);
		auto message = "Insert " + total_elements + " elements (insert at random index) [worst/average]";

		Timer timer(std::cerr, message);

		int lim = std::min(1, static_cast<int>(arr_1.size()));

		for (int i = 0; i < lim; ++i)
		{
			container.push_back(arr_1[i]);
		}

		for (auto &item: arr_1)
		{
			auto idx = Generator::pick_num(0, container.size() - 1);
			container.insert(idx, item);
		}
	}
	{
		UnrolledLinkedList container(n_array);
		std::vector<int> idxes;

		for (auto &item: arr_1)
		{
			container.push_back(item);
		}

		{
			auto message = "Find " + search_elements + " elements by value";

			Timer timer(std::cerr, message);

			for (auto &item: arr_2)
			{
				idxes.push_back(container.find(item));
			}
		}
	}
	{
		UnrolledLinkedList container(n_array);
		std::vector<int> vals;
		std::vector<int> gens;
		gens.reserve(arr_2.size());
		vals.reserve(arr_2.size());

		for (auto &item: arr_1)
		{
			container.push_back(item);
		}
		for (int i = 0; i < arr_2.size(); ++i)
		{
			gens.push_back(Generator::pick_num(0, arr_2.size() - 1));
		}
		{
			auto message = "Addressing by index " + std::to_string(arr_2.size()) + " times";

			Timer timer(std::cerr, message);

			for (int i = 0; i < arr_2.size(); ++i)
			{
				vals.push_back(container.at(gens[i]));
			}
		}
	}
	{
		UnrolledLinkedList container(n_array);

		for (auto &item: arr_1)
		{
			container.push_back(item);
		}
		{
			auto message = "Erase " + std::to_string(arr_2.size()) + " times";

			Timer timer(std::cerr, message);

			for (auto &item : arr_2)
			{
				container.erase(item);
			}
		}
	}
}

int main()
{
	// benchmark_unrolled_list(100, 1000, 10000, 4000);
	// call check
	return 0;
}