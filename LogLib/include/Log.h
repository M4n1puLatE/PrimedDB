#pragma once

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
		LogType m_logType = LogType::None;
		std::atomic_bool m_terminated = false;
		std::atomic_bool m_print = false;
		std::string_view get();
		void terminalBehaviour();
	public:
		static const char* GetLogTypeName(LogType logType);
		bool isTerminated() const;
		void ToFile(const string& fileName);
		Log& useTimeStamp(bool value);
		Log& printAnd();
		void print();
		void clear();
		void end();
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
	};
}

