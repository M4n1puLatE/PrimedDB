# pragma once
#include <Tester.h>
namespace Tester
{
	class TimeStampTester:public Tester<TimeStampTester>
	{ 
		THIS_IS_A_TEST(TimeStampTester);

		void init();
	};
}
