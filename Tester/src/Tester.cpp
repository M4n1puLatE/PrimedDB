//#include "Tester.h"
//#include <format>
//#include <iostream>
//#include <typeinfo>
//namespace Tester
//{
//	using namespace std;
//	Tester::Tester()
//        :m_useTimer(false)
//	{}
//	void Tester::add(const string& name, test_function test)
//	{
//		auto pair = make_pair(name, test);
//        m_tests.emplace(pair);
//	}
//	size_t Tester::size()const
//	{
//		return m_tests.size();
//	}
//	bool Tester::isTimerEnable() const
//	{
//		return m_useTimer;
//	}
//	void Tester::enableTimer()
//	{
//		m_useTimer = true;
//	}
//	void Tester::disableTimer()
//	{
//		m_useTimer = false;
//	}
//	void Tester::testBegin(const string& name)const
//	{
//		cout << format("[{}]\n________________________________________________", name) << endl;
//	}
//	void Tester::testEnd()
//	{
//		cout << "________________________________________________\n\n" << endl;
//	}
//	void Tester::activeTimer()
//	{
//		if (m_useTimer)
//		{
//			m_timer.start();
//		}
//	}
//	void Tester::printTimeCost()
//	{
//		if (m_timer.isStarted())
//		{
//			cout << format("> [Time cost: {}]\n", m_timer.end());
//		}
//	}
//	void Tester::testResult(test_pair& test)
//	{
//		cout << format("> Running [{}] is {}\n",
//			test.first,
//			(test.second() ? "passed" : "failed"));
//	}
//	void Tester::testLoop(size_t& testNumber, size_t& total)
//	{
//		unsigned n = 0;
//		while (!m_tests.empty())
//		{
//
//			auto test = std::move(m_tests.front());
//			testBegin(test.first);
//			m_tests.pop();
//			activeTimer();
//			testResult(test);
//			printTimeCost();
//			++testNumber;
//			++n;
//			testEnd();
//		}
//	}
//	void Tester::run()
//	{
//		size_t success = 0, total = m_tests.size();
//		cout << format("> {}\n", className(this)) << endl;
//		testLoop(success, total);
//		cout<< format("{} tests passed out of {}\n", success, total) << endl;
//	}
//}
//
