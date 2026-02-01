#include "Tester.h"
#include <format>
#include <iostream>
#include <typeinfo>
namespace Tester
{
	using namespace std;
	Tester::Tester(const char* name,Tester* actualTester)
        :m_name(name),m_useTimer(false)
	{
		actualTester->init();
	}
	void Tester::add(const string& name, test_function test)
	{
		auto pair = make_pair(name, test);
        m_tests.emplace(pair);
	}
	size_t Tester::size()const
	{
		return m_tests.size();
	}
	bool Tester::isTimerEnable() const
	{
		return m_useTimer;
	}
	void Tester::enableTimer()
	{
		m_useTimer = true;
	}
	void Tester::disableTimer()
	{
		m_useTimer = false;
	}
	void Tester::run()
	{
		bool pass = false;
		size_t testNumber = 0,total = m_tests.size();
		unsigned n = 0;
		while (!m_tests.empty())
		{
			cout << format("Test {}________________________________________",n+1)<<endl;
			auto test = std::move(m_tests.front());
			m_tests.pop();
			if (m_useTimer)
			{
				m_timer.start();
			}
			cout << format("Running {} is {}\n",
				test.first,
				(test.second() ? "passed" : "failed"));
			if (m_timer.isStarted())
			{
				cout << format("Time cost: {}", m_timer.end());
			}
			++testNumber;
			++n;
			cout << "______________________________________________\n" << endl;
		}
		cout<< format("{} tests passed out of {}", testNumber, total) << endl;
	}
}

