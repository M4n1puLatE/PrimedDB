//#include "ManagerTester.h"
//
//namespace Tester
//{
//	void ManagerTester::init()
//	{
//		this->add("testNotifyWithGoodCondition", TEST_FUNCTION(testNotifyWithGoodCondition));
//        this->add("testNotifyWithBadCondition", TEST_FUNCTION(testNotifyWithBadCondition));
//        this->add("testIsTerminate", TEST_FUNCTION(testIsTerminate));
//        this->add("testTerminate", TEST_FUNCTION(testTerminate));
//	}
//	bool ManagerTester::testIsTerminate()
//	{
//		return m_manager.isTerminate() == false;
//	}
//	bool ManagerTester::testNotifyWithGoodCondition()
//	{
//		
//	}
//	bool ManagerTester::testNotifyWithBadCondition()
//	{
//		
//	}
//	bool ManagerTester::testTerminate()
//	{
//		m_manager.terminate();
//		return m_manager.isTerminate() == true;
//	}
//	ManagerTester::ManagerTester()
//		:m_manager(m_testFunction,m_condition)
//	{
//		
//	}
//}
