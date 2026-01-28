#include "Tester.h"

#include <format>
#include <iostream>

namespace Tester
{
	using namespace std;
	Tester::Tester(const string& name)
		:m_name(name),m_useTimer(false)
	{}
	Tester::Tester(const string& name, bool useTimer)
		:m_name(name),m_useTimer(useTimer)
	{}
	void Tester::add(const string& name, test_function test)
	{
		auto pair = make_pair(name, test);
        m_tests.emplace(pair);
	}
	size_t Tester::size()const
	{
		return m_tests.size();
	}
	void Tester::run()
	{
		bool pass = false;
		size_t testNumber = 0;
		for (int n = 0;n<m_tests.size();++n)
		{
			auto& test = m_tests.front();
			m_tests.pop();
			if (test.second)
			{
				if (m_useTimer)
				{
					m_timer.start();
				}
				cout << format("Running {} is {}\n",
					test.first,
					(test.second()? "passed" : "failed"));
				if (m_timer.isStarted())
				{
					cout << format("Time cost: {}",m_timer.end());
				}
				testNumber++;
			}
		}
		cout<< format("{} tests passed out of {}", testNumber, m_tests.size()) << endl;
	}
}

