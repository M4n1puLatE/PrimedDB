#include "Random.h"

namespace Util::Math
{
    static std::random_device rd;
	std::mt19937_64 Random::sm_generator(rd())  ;
	long long RandomInt::generate(long long lower_bound, long long upper_bound)
	{
		if (lower_bound > upper_bound)
			return std::numeric_limits<long long>::min();
		std::uniform_int_distribution<long long>dis(lower_bound, upper_bound);
		return dis(Random::sm_generator);
	}
    long long RandomInt::generate(long long upper_bound)
    {
		if (upper_bound < 0)
			return 0;
        return generate(0, upper_bound);
    }
    long long RandomInt::generate(std::pair<long long, long long> range)
    {
		if (range.first > range.second)
			return std::numeric_limits<long long>::min();
        return generate(range.first, range.second);
    }
    double RandomFloat::generate(double lower_bound, double upper_bound)
    {
		if (lower_bound > upper_bound)
			return std::numeric_limits<double>::min();
        std::uniform_real_distribution<double>dis(lower_bound, upper_bound);
        return dis(Random::sm_generator);
    }
    double RandomFloat::generate(double upper_bound)
    {
		if (upper_bound < 0)
			return 0;
        return generate(0, upper_bound);
    }
    double RandomFloat::generate(std::pair<double, double> range)
    {
		if (range.first > range.second)
			return std::numeric_limits<double>::min();
        return generate(range.first, range.second);
    }
}
