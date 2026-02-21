#include "LogManager.h"

#include <iostream>
#include <fstream>
#include <functional>
namespace Log
{
	void LogManager::clear()
	{
		if (m_printCount > SUBMIT_COUNT)
		{
			m_printCount = 0;
		}
		printf("\n");
		++m_printCount;
	}
	LogManager::LogManager()
		:Manager(std::bind(&LogManager::task,this), std::bind(&LogManager::condition,this)),m_printCount(0)
	{}
	void LogManager::task()
	{
		std::pair<std::string, std::string> pair;
		{
			Util::write_lock lock(m_queueMutex);
			pair = std::move(m_writeQueue.front());
            m_writeQueue.pop();
		}
		//使用系统级文件操作
		std::fstream file(pair.first, std::ios::app);
		file << pair.second << std::endl;
	}
	bool LogManager::condition()const
	{
		return !m_writeQueue.empty();
	}
	void LogManager::print(const std::string& message)
	{
		Util::unique_lock lock(m_printProtect);
		printf(message.c_str());
		clear();
	}
	void LogManager::write(const std::string& fileDir, std::string&& message)
	{
		Util::write_lock lock(m_queueMutex);
		m_writeQueue.emplace(fileDir, std::move(message));
		if (m_printCount == SUBMIT_COUNT)
			notify();
	}
	void LogManager::write(std::string&& fileDir, std::string&& message)
	{
		Util::write_lock lock(m_queueMutex);
		m_writeQueue.emplace(std::forward<std::string>(fileDir), std::forward<std::string>(message));
		if (m_printCount == SUBMIT_COUNT)
			notify();
	}
	size_t LogManager::size()
	{
		Util::read_lock lock(m_queueMutex);
		return m_writeQueue.size();
	}
	bool LogManager::isEmpty()
	{
		Util::read_lock lock(m_queueMutex);
        return m_writeQueue.empty();
	}
}
