#include "LogTester.h"
#include "Log.h"

namespace Tester
{
	class TestObject
	{
	public:
		std::string format()const
		{
			return "object";
		}
	};
	void clear()
	{
		Log::log.clear();
	}
	void LogTester::init()
	{
		enableTimer();
		add("testAdd", TEST_FUNCTION(testAdd));
        add("testAddNumber", TEST_FUNCTION(testAddNumber));
        add("testAddDouble", TEST_FUNCTION(testAddDouble));
        add("testAddObject", TEST_FUNCTION(testAddObject));
        add("testGetLogTypeName", TEST_FUNCTION(testGetLogTypeName));
		add("testEnd", TEST_FUNCTION(testEnd));
        add("testPrint", TEST_FUNCTION(testPrint));
        add("testWrite", TEST_FUNCTION(testWrite));
        add("testEmpty", TEST_FUNCTION(testEmpty));
		add("Just Print", TEST_FUNCTION(justPrint));
	}
	bool LogTester::testAdd()
	{
		Log::log.add("hello");
		bool c = !Log::log.isEmpty();
		clear();
		return c;
	}
	bool LogTester::testAddNumber()
	{
		Log::log.addNumber(1000l);
		bool c = !Log::log.isEmpty();
		clear();
		return c;
	}
	bool LogTester::testAddDouble()
	{
		Log::log.addDouble(114.514);
		bool c = !Log::log.isEmpty();
		clear();
		return c;
	}
	bool LogTester::testAddObject()
	{
		TestObject obj;
        Log::log.addObject(obj);
        bool c = !Log::log.isEmpty();
        clear();
        return c;
	}
	bool LogTester::testGetLogTypeName()
	{
		cout << Log::Log::GetLogTypeName(Log::LogType::None) << "\n";
        cout << Log::Log::GetLogTypeName(Log::LogType::Debug) << "\n";
        cout << Log::Log::GetLogTypeName(Log::LogType::Error) << "\n";
        cout << Log::Log::GetLogTypeName(Log::LogType::Fatal) << "\n";
        cout << Log::Log::GetLogTypeName(Log::LogType::Info) << "\n";
        cout << Log::Log::GetLogTypeName(Log::LogType::Warn) << std::endl;
		return true;
	}
	bool LogTester::testEnd()
	{
		Log::log.add("hello").end();
        return Log::log.isTerminated();
	}

	bool LogTester::testPrint()
	{
		Log::log.type(Log::LogType::Info).add("Test").add("Info").addNumber(1).end();
		return true;
	}
	bool LogTester::testWrite()
	{
		for (int n = 0;n<1000;++n)
		{
			Log::log.type(Log::LogType::Info).add("Test").add("Info").addNumber(1).toFile("test").end();
			Log::log.type(Log::LogType::Info).add("Test").add("Info").addNumber(2).toFile("test").end();
			Log::log.type(Log::LogType::Info).add("Test").add("Info").addNumber(3).toFile("test").end();
			Log::log.type(Log::LogType::Info).add("Test").add("Info").addNumber(4).toFile("test").end();
			Log::log.type(Log::LogType::Info).add("Test").add("Info").addNumber(5).toFile("test").end();
		}

		return true;
	}
	bool LogTester::justPrint()
	{
		for (int n = 0; n < 1000; ++n)
		{
			string message = "combine";
			message += +"messages";
			printf("%s\n", message.c_str());
			message += +"messages";
			printf("%s\n", message.c_str());
			message += +"messages";
			printf("%s\n", message.c_str());
			message += +"messages";
			printf("%s\n", message.c_str());
			message += +"messages";
			printf("%s\n", message.c_str());
		}
		return true;
	}
	bool LogTester::testEmpty()
	{
		bool c=  Log::log.isEmpty();
		Log::log.add("hello");

		return c && !Log::log.isEmpty();
	}
}
 