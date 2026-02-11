#pragma once
#include <deque>
#include <queue>

#include "Manager.h"
#include "Singleton.h"

namespace Log
{
	class LogManager final:public Util::Singleton<LogManager>,public Util::Manager
	{ 
		THIS_IS_SINGLETON;
		std::queue<std::pair<std::string, std::string>> m_writeQueue;
		std::atomic_uint8_t m_printCount;
		std::shared_mutex m_queueMutex;

		void clear();
		LogManager();
		void writeTask();
		bool condition() const; 

	public:
		void print(const std::string& message);
		void write(std::string&& fileDir, std::string&& message);
		void write(const std::string& fileDir, std::string&& message);
		size_t size();
		bool isEmpty();


		~LogManager()=default;
	};
}
