#include "Generator.hpp"
#include <random>

std::vector<int> Generator::gen_range(int size, int from, int to)
{
	std::vector<int> range;
	range.reserve(size);

	for (int i = 0; i < size; ++i)
	{
		range.push_back(pick_num(from, to));
	}
	return range;
}
int Generator::pick_num(int from, int to)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(from, to);
	return dis(gen);
}
Generator::Generator() = default;
