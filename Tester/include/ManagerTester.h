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

		bool testIsTerminate();
		bool testNotifyWithGoodCondition();
        bool testNotifyWithBadCondition();
		bool testTerminate();
	public:
		ManagerTester()=default;
	};
}
