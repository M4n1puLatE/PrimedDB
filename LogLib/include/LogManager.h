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
		const uint8_t SUBMIT_COUNT = 255;
		std::queue<std::pair<std::string, std::string>> m_writeQueue;
		std::atomic_uint8_t m_printCount;
		std::shared_mutex m_queueMutex;
		std::mutex m_printProtect;
		void clear();
		LogManager();
		void task();
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
