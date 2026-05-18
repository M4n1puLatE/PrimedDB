#pragma once
#include <random>

namespace Util::Math
{
	class Random
	{
	public:
		static std::mt19937_64 sm_generator;
	};
	class RandomInt
	{
	public:
		static long long generate(long long lower_bound, long long upper_bound);
		static long long generate(long long upper_bound);
		static long long generate(std::pair<long long, long long> range);
		
	};
	class RandomFloat
	{
	public:
		static double generate(double lower_bound, double upper_bound);
		static double generate(double upper_bound);
		static double generate(std::pair<double, double> range);
	};
}
