#include "Manager.h"

namespace Util
{
	void Manager::service(const std::function<void()>& customService,const std::function<bool()>& condition)
	{
		m_conditionLock = std::unique_lock<std::mutex>(m_conditionMutex);
		while (true)
		{
			m_threadNotifier.wait(m_conditionLock,condition);
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
	Manager::~Manager()
	{
		m_service.join();
	}
}
