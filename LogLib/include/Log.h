#include <string>
#include <iostream>
#include <sstream>
#include <format>
#include <future>
#include <queue>
#include <shared_mutex>

namespace Log
{
	enum class LogType
	{
        Error,
        Warn,
        Info,
        Debug,
		Fatal
	};
	class Log
	{
		using string = std::string;
		std::stringstream m_messageStream;
		std::string_view m_fileName;
	public:
		Log add(const std::string& text);
		Log addNumber(size_t number);
		Log addDouble(double number);
		void ToFile(const string& fileName);
		void useTimeStamp(bool value);
		Log printAnd();
		void clear();
		void end();
		std::string_view get();
	};
}

