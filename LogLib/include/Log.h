#pragma once
#include <TimeStamp.h>
#include <string>
#include <iostream>
#include <sstream>
#include <format>
#include <future>
#include <queue>
#include <shared_mutex>

namespace Log
{
	template <typename T>
	concept FormatType = requires(T instance)
	{
		instance.format();
	};
	enum class LogType
	{
		None,
		Info,
		Debug,
        Warn,
		Error,
		Fatal
	};
	class Log;
	static void endl(Log& obj);
	class Log
	{
		using string = std::string;


		std::stringstream m_messageStream;
		LogType m_logType = LogType::None;
		string m_fileName;
		bool m_useTimeStamp = false;

		const std::string& getFileName() const;
		const std::string& getMessage()const;
		std::string getLabel() const;
	public:
		static const char* GetLogTypeName(LogType logType);
		bool isTerminated();
		bool isUseTimeStamp() const;
		bool isWriteToFile() const;

		Log& Log::ToFile(string& fileName);
        Log& Log::useTimeStamp();
		friend void endl(Log&);
		void end();
		void clear();
		bool empty();
		Log& trigger(const string& error);


		Log& add(const std::string& text);
		Log& addNumber(size_t number);
		Log& addDouble(double number);
		template<FormatType T>
		Log& addObject(const T& instance)
		{
			m_messageStream <<instance.format();
			return *this;
		}
		Log& operator<<(const string& text);
        Log& operator<<(size_t number);
        Log& operator<<(double number);
		template<FormatType T>
		Log& operator<<(const T& instance)
		{
			m_messageStream << instance.format();
			return *this;
		}

		void operator<<(void (*func)(Log*));
	};
}

