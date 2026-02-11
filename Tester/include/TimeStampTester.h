# pragma once
#include <Tester.h>
#include "TimeStamp.h"
namespace Tester
{
	class TimeStampTester:public Tester<TimeStampTester>
	{ 
		THIS_IS_A_TEST(TimeStampTester);
		static void printTime(Util::TimeStamp& ts);
		void init();

		static bool testGetString();
		static bool testGetTimeNumber();
		static bool testReset();
		static bool testClear();
		static bool testIsEmpty();
		static bool testCompare();
		static bool testIsEarlier();
		static bool testIsLater();
		static bool testGet();
		static bool testGetDate();
		static bool testDistance();
		static bool testAddMinus();


	public:
		TimeStampTester()=default;
	};
}
