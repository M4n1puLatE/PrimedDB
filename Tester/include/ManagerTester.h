#pragma once
#include "Manager.h"
#include "Tester.h"
using namespace Util;
namespace Tester
{
	class ManagerTester : public Tester<ManagerTester>
	{ 
		THIS_IS_A_TEST(ManagerTester);
		void init();
		
		Manager m_manager;
		int m_size = 10;
		auto m_testFunction = []()
			{
				cout << "thread running" << endl;
			};
		auto m_condition = [this]()
		{
			return m_size == 10;
		};
		bool testIsTerminate();
		bool testNotifyWithGoodCondition();
        bool testNotifyWithBadCondition();
		bool testTerminate();
	public:
		ManagerTester();
	};
}
