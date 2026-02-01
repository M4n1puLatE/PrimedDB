#pragma once
#include <functional>
#include <queue>
#include <string>
#include <vector>
#include <Timer.h>
#include <iostream>
#include <algorithm>
#include <ranges>

namespace Tester
{
#define TEST_FUNCTION(function) [this](){return function();}
	//用于进行单元测试
	//非线程安全类
	class Tester
	{
	protected:
		using string = std::string;
		using test_function = std::function<bool()>;
		using test_pair = std::pair<string, test_function>;
		template<class T>
		static void printVector(const std::vector<T>& vec)
		{
			std::cout << "[";
			for (int n = 0;n<vec.size();++n)
			{
				std::cout << vec[n];
				if (n+1<vec.size())
				{
					std::cout << ",";
				}
			}
            std::cout << "]" << std::endl;
		}
		template <std::ranges::range T>
		static bool collectionEqual(const T& c1,const T& c2)
		{
			if (c1.size() != c2.size())
				return false;
			return std::equal(c1.begin(), c1.end(), c2.begin());;
		}
		void enableTimer();
		void disableTimer();
		void add(const string& name, test_function test);
		virtual void init() = 0;
		Tester(const char*,Tester* actualTester);
	private:
		const string& m_name;
		std::queue <test_pair> m_tests;
		Util::Timer<Util::milliseconds> m_timer;
		bool m_useTimer;
	public:
		size_t size()const;
		bool isTimerEnable() const;
		void run();
		virtual ~Tester() = default;
	};
}
