#include "LogTester.h"
#include "Log.h"
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp> // 用于控制台输出
#include <boost/log/utility/setup/common_attributes.hpp> // 用于添加时间戳等属性

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
		namespace logging = boost::log;
		logging::add_common_attributes();

		// 添加一个控制台日志接收器 (sink)，使用默认格式
		logging::add_console_log();
		for (int n = 0; n < 1000; ++n)
		{


			// --- 记录日志 ---
			// 使用内置的严重性级别
			BOOST_LOG_TRIVIAL(warning) << "This is a warning message.";
			BOOST_LOG_TRIVIAL(error) << "This is an error message.";
			BOOST_LOG_TRIVIAL(fatal) << "This is a fatal message.";
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
 