#include "ManagerTester.h"

namespace Tester
{
	
	class TestManager : public Manager
	{
		
		//std::function<void()> m_testFunction = []()
		//{
		//	cout << "thread running" << endl;
		//};
		//std::function<bool()> m_condition = [this]()
		//{
		//	return m_boolvalue;
		//};
	public:
		bool m_boolvalue = true;
		TestManager()
			:Manager(std::move([]()
		{
			cout << "thread running" << endl; std::this_thread::sleep_for(seconds(5));
		}), std::move([this]()
		{
			return m_boolvalue;
		}))
		{
			
		}
		void notify()
		{
			Manager::notify();
		}
	} manager;
	void ManagerTester::init()
	{
		this->add("testNotifyWithGoodCondition", TEST_FUNCTION(testNotifyWithGoodCondition));
        this->add("testNotifyWithBadCondition", TEST_FUNCTION(testNotifyWithBadCondition));
        this->add("testIsTerminate", TEST_FUNCTION(testIsTerminate));
        this->add("testTerminate", TEST_FUNCTION(testTerminate));
	}
	bool ManagerTester::testIsTerminate()
	{
		return manager.isThreadEmpty() == false;
	}
	bool ManagerTester::testNotifyWithGoodCondition()
	{
        manager.m_boolvalue = true;
		int threadCount = 0;
		for (int n = 0;n<1000;++n)
		{
			manager.notify();
			if (threadCount != manager.threadSize())
			{
				cout <<std::format("now we have {}", manager.threadSize())<<std::endl;
                threadCount = manager.threadSize();
			}
		}
		std::this_thread::sleep_for(seconds(30));
		return true;
	}
	bool ManagerTester::testNotifyWithBadCondition()
	{
		manager.m_boolvalue = false;
		manager.notify();
		return true;
	}
	bool ManagerTester::testTerminate()
	{
		manager.terminate();
		return manager.isThreadEmpty() == true;
	}
}
