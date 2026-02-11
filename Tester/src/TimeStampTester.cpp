#include <TimeStampTester.h>



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
	void TimeStampTester::printTime(Util::TimeStamp& ts)
	{
		std::cout << std::format("{} - {}", ts.get(), ts.getTimestamp()) << "\n";
	}

	bool TimeStampTester::testGetString()
	{
		Util::TimeStamp timeStamp = Util::TimeStamp::Now();
		cout << timeStamp.get()<<std::endl;
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
		auto str = timeStamp.get();
		printTime(timeStamp);
		auto newTime = Util::TimeStamp::Now();
        timeStamp.reset(newTime);
		printTime(timeStamp);
		cout << endl;
		return str != timeStamp.get();
	}
	bool TimeStampTester::testClear()
	{
		Util::TimeStamp timeStamp = Util::TimeStamp::Now();
		printTime(timeStamp);
        timeStamp.clear();
		printTime(timeStamp);
		cout << endl;
		return timeStamp.isEmpty();
	}
	bool TimeStampTester::testIsEmpty()
	{
		Util::TimeStamp timeStamp;
		printTime(timeStamp);
		bool empty = timeStamp.isEmpty();
		auto now = Util::TimeStamp::Now();
		timeStamp.reset(now);
		printTime(timeStamp);
		return timeStamp.isEmpty()!= empty;
	}
	bool TimeStampTester::testCompare()
	{
		Util::TimeStamp t1 = Util::TimeStamp::Now(),t2 = Util::TimeStamp::Now();
		printTime(t1);
		printTime(t2);
		cout << std::endl;
        return t1.compare(t2);
	}
	bool TimeStampTester::testIsEarlier()
	{
		Util::TimeStamp t1 = Util::TimeStamp::Now();
		std::this_thread::sleep_for(Util::milliseconds(50));
		Util::TimeStamp t3 = Util::TimeStamp::Now();
        return t1.isEarlier(t3) ;

	}
	bool TimeStampTester::testIsLater()
	{
		Util::TimeStamp t1 = Util::TimeStamp::Now();
		std::this_thread::sleep_for(Util::milliseconds(50));
		Util::TimeStamp t3 = Util::TimeStamp::Now();
		printTime(t1);
		printTime(t3);
		return t3.isLater(t1);
	}
	bool TimeStampTester::testGet()
	{
		Util::TimeStamp t1 = Util::TimeStamp::Now();
		printTime(t1);
		return true;
	}
	bool TimeStampTester::testGetDate()
	{
		Util::TimeStamp t1 = Util::TimeStamp::Now();
		printTime(t1);
		cout<< std::format("Date: {}", t1.getDate())<<"\n";
        cout << std::format("Day: {}", t1.get(Util::TimeType::Day)) << "\n";
		cout<<std::format("Month: {}", t1.get(Util::TimeType::Month))<< "\n";
        cout << std::format("Year: {}", t1.get(Util::TimeType::Year)) << "\n";
        cout << std::format("Hour: {}", t1.get(Util::TimeType::Hour)) << "\n";
        cout << std::format("Minus: {}", t1.get(Util::TimeType::Minute)) << "\n";
        cout << std::format("Seconds: {}", t1.get(Util::TimeType::Second)) << std::endl;
		return !t1.get().empty();
	}
	bool TimeStampTester::testDistance()
	{
		Util::TimeStamp t1 = Util::TimeStamp::Now();
		std::this_thread::sleep_for(Util::milliseconds(50));
		Util::TimeStamp t2 = Util::TimeStamp::Now();
		printTime(t1);
		printTime(t2);
		cout<< t1.distance(t2)<<std::endl;
        return t1.distance(t2) < 0;
	}
	bool TimeStampTester::testAddMinus()
	{
		Util::TimeStamp t1 = Util::TimeStamp::Now();
		printTime(t1);
		t1.add(Util::seconds(12));
		printTime(t1);
		t1.minus(Util::seconds(12));
        printTime(t1);
		return true;
	}

}
