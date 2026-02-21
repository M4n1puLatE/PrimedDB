#include "Manager.h"

namespace Util
{
	//void DepreciatedManager::service(const std::function<void()>& customService,const std::function<bool()>& condition)
	//{
	//	unique_lock conditionLock = unique_lock(m_conditionMutex);
	//	while (true)
	//	{
	//		m_threadNotifier.wait(conditionLock, [this,condition]()
	//			{
	//				return condition() || m_terminate;
	//			}
	//		);
	//		if (m_terminate)
	//			break;
	//		customService();
	//	}
	//}
	//DepreciatedManager::DepreciatedManager(const std::function<void()>& customService, const std::function<bool()>& condition)
	//	:m_terminate(false)
	//{
	//	m_service = std::thread(&DepreciatedManager::service,this,customService,condition);
	//}
	//void DepreciatedManager::notify()
	//{
	//	m_threadNotifier.notify_one();
	//}
	//bool DepreciatedManager::isTerminate()
	//{
	//	return m_terminate;
	//}
	//void DepreciatedManager::terminate()
	//{
	//	m_terminate = true;
	//	notify();
	//	join();
	//}

	//void DepreciatedManager::join()
	//{
	//	if (m_service.joinable())
	//		m_service.join();
	//}

	//DepreciatedManager::~DepreciatedManager()
	//{
	//	terminate();
	//}

	/////////////////////////////////////////////
	std::thread Manager::sm_service = std::thread(&Manager::manageService);
	mutex Manager::sm_conditionMutex;
	std::condition_variable Manager::sm_threadNotifier;
	std::atomic_bool Manager::sm_terminate = false;
	std::atomic_bool Manager::sm_conditionFlag = false;


	std::vector<Manager::service> Manager::sm_serviceArray;
	
	std::deque<size_t> Manager::sm_executeQueue;
	shared_mutex Manager::sm_containerMutex;

	void Manager::manageService()
	{
		unique_lock lock = unique_lock(sm_conditionMutex);
		size_t index = 0;
		while (true)
		{
			sm_threadNotifier.wait(lock, []()
				{
					return sm_terminate || (sm_conditionFlag &&!(isEmpty()||isServiceEmpty()));
				}
			);
			if (sm_terminate)
			{
				break;
			}
			bool run = false;
			{
				read_lock lock(sm_containerMutex);
				run = !sm_executeQueue.empty();
			}
			while(run)
			{
				{
					write_lock queueLock(sm_containerMutex);
					index = sm_executeQueue.front();
					sm_executeQueue.pop_front();
					sm_conditionFlag = run = !sm_executeQueue.empty();
				}
				sm_serviceArray[index]();
			}
		}
	}
	void Manager::add(service&& serviceFunc)
	{
		if (!sm_terminate)
		{
			write_lock queueLock(sm_containerMutex);
			sm_serviceArray.emplace_back(std::move(serviceFunc));
		}
	}

	void Manager::newTask(size_t id)
	{
		if (!sm_terminate)
		{
			write_lock queueLock(sm_containerMutex);
			sm_executeQueue.emplace_back(id);
		}

	}

	void Manager::urgentTask(size_t id)
	{
		if (!sm_terminate)
		{
			write_lock queueLock(sm_containerMutex);
            sm_executeQueue.emplace_front(id);
		}
	}

	bool Manager::isEmpty()
	{
		read_lock lock(sm_containerMutex);
		return sm_executeQueue.empty();
	}
	bool Manager::isServiceEmpty()
	{
		read_lock lock(sm_containerMutex);
		return sm_serviceArray.empty();
	}

	size_t Manager::serviceSize()
	{
		read_lock queueLock(sm_containerMutex);
		return sm_serviceArray.size();
	}

	size_t Manager::taskSize()
	{
		read_lock queueLock(sm_containerMutex);
        return sm_executeQueue.size();
	}

	Manager::Manager(std::function<void()>&& customService, std::function<bool()>&& condition)
		:m_condition(std::move(condition)),m_id(serviceSize())
	{
		add(std::move(customService));
	}
	void Manager::notify()const
	{
		if (!isTerminate())
		{
			bool condition = m_condition();
			submit();
			if (condition&&!sm_conditionFlag)//如果当前仍然处于执行期，则不额外进行通知
			{
				sm_conditionFlag = condition;
				sm_threadNotifier.notify_one();
			}
		}
	}
	void Manager::notifyNow()const
	{
		if (!isTerminate())
		{
			bool condition = m_condition();
			urgentTask(m_id);
			if (condition && !sm_conditionFlag)
			{
				sm_conditionFlag = condition;
				sm_threadNotifier.notify_one();
			}
		}
	}
	void Manager::submit()const
	{
		newTask(m_id);
	}

	bool Manager::isTerminate()
	{
		return sm_terminate;
	}

	void Manager::join()
	{
		if (sm_service.joinable())
            sm_service.join();
	}
	void Manager::terminate()
	{
		notifyTerminate();
		
		join();
	}
	void Manager::notifyTerminate()
	{
		sm_terminate = true;
		sm_threadNotifier.notify_one();
	}
}
