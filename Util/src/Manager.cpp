#include "Manager.h"

namespace Util
{
	void Manager::service(const std::function<void()>& customService,const std::function<bool()>& condition)
	{
		unique_lock conditionLock = unique_lock(m_conditionMutex);
		while (true)
		{
			m_threadNotifier.wait(conditionLock, [this,condition]()
				{
					return condition() || m_terminate;
				}
			);
			if (m_terminate)
				break;
			customService();
		}
	}
	Manager::Manager(const std::function<void()>& customService, const std::function<bool()>& condition)
		:m_terminate(false)
	{
		m_service = std::thread(&Manager::service,this,customService,condition);
	}
	void Manager::notify()
	{
		m_threadNotifier.notify_one();
	}
	bool Manager::isTerminate()
	{
		return m_terminate;
	}
	void Manager::terminate()
	{
		m_terminate = true;
		notify();
		join();
	}

	void Manager::join()
	{
		if (m_service.joinable())
			m_service.join();
	}

	Manager::~Manager()
	{
		terminate();
	}
}
