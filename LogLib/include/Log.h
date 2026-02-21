#pragma once
#include <TimeStamp.h>
#include <string>
#include <sstream>
#include <future>
#include <deque>

namespace Log
{
	template <typename T>
	concept FormatType = requires(const T& instance)
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

	class Log
	{
		using string = std::string;


		std::deque<string> m_messageArray;
		LogType m_logType = LogType::None;
		string m_fileName;

		const std::string& getFileName() const;
		std::string getMessage()const;
		std::string getLabel() const;
		void writeTask(string& message) const;
		static void printMessage(const string& message);
	public:
		static string GetLogTypeName(LogType logType);
		bool isTerminated() const;
		bool isWriteToFile() const;
		Log& type(LogType logType);

		Log& toFile(string&& fileName);
		friend void endl(Log&);
		void end();
		void clear();
		bool isEmpty();
		Log& trigger(const string& error);

		

		Log& add(std::string& text);
		Log& add(std::string&& text);
		Log& addNumber(size_t number);
		Log& addDouble(double number);
		template<FormatType T>
		Log& addObject(const T& instance)
		{
			m_messageArray.emplace_back(std::move(instance.format()));
			return *this;
		}
		Log& operator[](LogType logType);
		Log& operator()(string&& fileName);
		Log& operator<<(string& text);
		Log& operator<<(string&& text);
        Log& operator<<(size_t number);
        Log& operator<<(double number);
		template<FormatType T>
		Log& operator<<(const T& instance)
		{
			m_messageArray.emplace_back(std::move(instance.format()));
			return *this;
		}

		void operator<<(void (*func)(Log&)); 
		static void endl(Log& obj);
	};
	static Log log;
}

