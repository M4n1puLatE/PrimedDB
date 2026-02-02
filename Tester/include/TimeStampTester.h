# pragma once
#include <Tester.h>
namespace Tester
{
	class TimeStampTester:public Tester<TimeStampTester>
	{ 
		THIS_IS_A_TEST(TimeStampTester);

		void init();

		bool testGetString();
		bool testGetTimeNumber();
		bool testReset();
		bool testClear();
		bool testIsEmpty();
		bool testCompare();
		bool testIsEarlier();
		bool testIsLater();
		bool testGet();
		bool testGetDate();
		bool testDistance();
		bool testAddMinus();

	public:
		TimeStampTester();
	};
}
