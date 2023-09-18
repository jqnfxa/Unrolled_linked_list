#include "Timer.hpp"

Timer::Timer(std::ostream &out, std::string message) : out_(out), message_(std::move(message))
{
	start_time_ = std::chrono::high_resolution_clock::now();
}
Timer::~Timer()
{
	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time_).count();
	out_ << message_ << " " << duration << " ms" << std::endl;
}
