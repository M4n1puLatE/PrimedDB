#include <TimeStampTester.h>

#include "TimeStamp.h"

namespace Tester
{
	void TimeStampTester::init()
	{
		add("TestGetString", TEST_FUNCTION(testGetString));
        add("TestGet", TEST_FUNCTION(testGet));
        add("TestGetTimeNumber", TEST_FUNCTION(testGetTimeNumber));
        add("TestGetDate", TEST_FUNCTION(testGetDate));
        add("TestIsEarlier", TEST_FUNCTION(testIsEarlier));
        add("TestIsLater", TEST_FUNCTION(testIsLater));
        add("TestIsEmpty", TEST_FUNCTION(testIsEmpty));
        add("TestReset", TEST_FUNCTION(testReset));
        add("TestAddMinus", TEST_FUNCTION(testAddMinus));
        add("TestDistance", TEST_FUNCTION(testDistance));
        add("TestCompare", TEST_FUNCTION(testCompare));
        add("TestClear", TEST_FUNCTION(testClear));
        enableTimer();
	}

	bool TimeStampTester::testGetString()
	{
		Util::TimeStamp timeStamp = Util::TimeStamp::Now();
		cout << timeStamp.getString()<<endl;
		return true;
	}
	bool TimeStampTester::testGetTimeNumber()
	{
		Util::TimeStamp timeStamp = Util::TimeStamp::Now();
		cout << timeStamp.getTimestamp() << endl;
		return true;
	}
	bool TimeStampTester::testReset()
	{
		Util::TimeStamp timeStamp = Util::TimeStamp::Now();
		auto str = timeStamp.getString();
		cout << str << endl;
		auto newTime = Util::TimeStamp::Now();
        timeStamp.reset(newTime);
		cout<<timeStamp.getString()<<endl;
		return str != timeStamp.getString();
	}
	bool TimeStampTester::testClear()
	{
		Util::TimeStamp timeStamp = Util::TimeStamp::Now();

	}
	bool TimeStampTester::testIsEmpty()
	{
		
	}
	bool TimeStampTester::testCompare()
	{
		
	}
	bool TimeStampTester::testIsEarlier()
	{
		
	}
	bool TimeStampTester::testIsLater()
	{
		
	}
	bool TimeStampTester::testGet()
	{
		
	}
	bool TimeStampTester::testGetDate()
	{
		
	}
	bool TimeStampTester::testDistance()
	{
		
	}
	bool TimeStampTester::testAddMinus()
	{
		
	}

	TimeStampTester::TimeStampTester()
	{
		
	}
}
