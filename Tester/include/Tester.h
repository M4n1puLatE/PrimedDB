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
#define THIS_IS_A_TEST(Self) friend class Tester<Self>
	//用于进行单元测试
	//非线程安全类
	template <class DerivedTest>

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
		template <std::derived_from<Tester> T>
		static const char* className(T* instance)
		{
			return typeid(*instance).name();
		}
		void enableTimer()
		{
			m_useTimer = true;
		}
		void disableTimer()
		{
			m_useTimer = false;
		}
		void add(const string& name, test_function test)
		{
			auto pair = make_pair(name, test);
			m_tests.emplace(pair);
		}
		Tester()
		{
			static_cast<DerivedTest*>(this)->init();
		}
	private:
		std::queue <test_pair> m_tests;
		Util::Timer<Util::milliseconds> m_timer;
		bool m_useTimer;
		static void printWithGreen(const string& message)
		{
			std::cout << std::format("\033[32m{}\033[0m",message) << std::endl;
		}
		static void printWithRed(const string& message)
		{
			std::cout << std::format("\033[31m{}\033[0m", message) << std::endl;
		}
		static void printWithYellow(const string& message)
		{
			std::cout << std::format("\033[33m{}\033[0m", message) << std::endl;
		}
		static void printWithBlue(const string& message)
		{
			std::cout << std::format("\033[104m{}\033[0m", message) << std::endl;
		}
		static void printWithFrontRed(const string& message)
		{
			std::cout << std::format("\033[30;107m{}\033[0m", message) << std::endl;
		}
		void testLoop(size_t& testNumber,size_t& total)
		{
			unsigned n = 0;
			while (!m_tests.empty())
			{
				auto test = std::move(m_tests.front());
				testBegin(n,test.first);
				m_tests.pop();
				activeTimer();
				testResult(test);
				printTimeCost();
				++testNumber;
				++n;
				testEnd();
			}
		}
		void printTimeCost()
		{
			if (m_timer.isStarted())
			{
				printWithBlue(std::format("> [Time cost: {}]", m_timer.end()));
			}
		}
		static void testBegin(unsigned series,const string& name)
		{
			printWithYellow(std::format("\n\n{}.[{}]", series + 1, name));
			std::cout << "________________________________________________"<<std::endl;
		}
		void testEnd()
		{
			std::cout << "________________________________________________" << std::endl;
		}
		void activeTimer()
		{
			if (m_useTimer)
			{
				m_timer.start();
			}
		}
		static void testResult(test_pair& test)
		{
			if (test.second())
			{
				printWithGreen(std::format("> Running [{}] is {}", test.first, "passed"));
			}
			else
			{
				printWithRed(std::format("> Running [{}] is {}", test.first, "failed"));
			}
		}
	public:
		size_t size()const
		{
			return m_tests.size();
		}
		bool isTimerEnable() const
		{
			return m_useTimer;
		}
		void run()
		{
			size_t success = 0, total = m_tests.size();
			string className = Tester::className(this);
			printWithFrontRed(std::format(">>> {} <<<", className.substr(className.find_last_of("::") + 1)));
			testLoop(success, total);
			printWithYellow(std::format("{} tests passed out of {}\n\n\n\n", success, total));
		}
		virtual ~Tester() = default;
	};
}
