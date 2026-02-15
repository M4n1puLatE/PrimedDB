#pragma once
#include <MultiThread.h>
namespace Util
{

	class Manager
	{
		std::thread m_service;
		mutex m_conditionMutex;
		std::condition_variable m_threadNotifier;
		std::atomic_bool m_terminate;	
		void service(const std::function<void()>& customService, const std::function<bool()>& condition);
	protected:

		void notify();
		void terminate();
		void join();
	public:
		
		Manager(const std::function<void()>& customService, const std::function<bool()>& condition);
		bool isTerminate();

		~Manager();
	};
}
