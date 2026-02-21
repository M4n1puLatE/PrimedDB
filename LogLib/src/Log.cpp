#include <Log.h>
#include <fstream>
#include <iostream>

#include "LogManager.h"

namespace Log
{
	std::string Log::GetLogTypeName(LogType logType)
	{
		if (logType == LogType::Debug)
            return " [Debug]";
        if (logType == LogType::Error)
            return " [Error]";
        if (logType == LogType::Fatal)
            return " [Fatal]";
        if (logType == LogType::Info)
            return " [Info]";
		if (logType == LogType::Warn)
			return " [Warn]";
		return "";
	}
	bool Log::isTerminated()const
	{
		return m_messageArray.empty();
	}

	Log& Log::toFile(string&& fileName)
	{
		m_fileName = std::move(fileName);
		m_fileName += ".log";
        return *this;
	}
	bool Log::isWriteToFile() const
	{
		return !m_fileName.empty();
	}
	void Log::clear()
	{
		m_messageArray.clear();
		m_fileName.clear();
        m_logType = LogType::None;
	}
	bool Log::isEmpty()
	{
		return m_messageArray.empty();
	}


	Log& Log::add(std::string& text)
	{
		if (!isEmpty())
		{
			m_messageArray.emplace_back(" ");
		}
		m_messageArray.emplace_back(text);
		return *this;
	}
	Log& Log::add(std::string&& text)
	{
		if (!isEmpty())
		{
			m_messageArray.emplace_back(" ");
		}
		m_messageArray.emplace_back(std::move(text));
		return *this;
	}
	Log& Log::addNumber(size_t number)
	{
		return add(std::to_string(number));
	}
	Log& Log::addDouble(double number)
	{
		return add(std::to_string(number));
	}
	Log& Log::operator<<(string& text)
	{
		return add(text);
	}
	Log& Log::operator<<(string&& text)
	{
		return add(std::move(text));
	}
	Log& Log::operator<<(size_t number)
	{
		return addNumber(number);
	}
	Log& Log::operator<<(double number)
	{
		return addDouble(number);
	}
	Log& Log::type(LogType logType)
	{
		m_logType = logType;
		return *this;
	}
	Log& Log::operator[](LogType logType)
	{
		return type(logType);
	}
	std::string Log::getLabel() const
	{
		return GetLogTypeName(m_logType);
	}
	const std::string& Log::getFileName() const
	{
		return m_fileName;
	}
	std::string Log::getMessage()const
	{
		string message;
		message.reserve(100);
        for (auto& item : m_messageArray)
        {
            message += item;
        }
		return message;
	}
	//提交到LogManger统一处理打印。
	void Log::writeTask(std::string& message) const
	{
		LogManager::Get().write(m_fileName, std::move(message));
	}
	//通知LogManager打印完成，当达到一定数量时清空缓存。
	void Log::printMessage(const string& message)
	{
		LogManager::Get().print(message);
	}
	void Log::end()
	{
		std::string print = getMessage();
		auto label = getLabel();

		Util::TimeStamp time = Util::TimeStamp::Now();
		print = std::format("{}{}: {}", time.get(),label,print);
		printMessage(print);
		if (isWriteToFile())
		{
			writeTask(print);
		}
		clear();
	}
	Log& Log::trigger(const string& error)
	{
		//Trigger error manager with a specific error.
		std::cout << "Trigger not fully implemented yet."<<"\n";
		return *this;
	}
	Log& Log::operator()(std::string&& fileName)
	{
		return toFile(std::forward<string>(fileName));
	}
	void Log::operator<<(void (*func)(Log&))
	{
		func(*this);
	}
	void Log::endl(Log& obj)
	{
		obj.end();
	}
}
