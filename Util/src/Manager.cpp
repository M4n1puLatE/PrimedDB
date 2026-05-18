#include "Manager.h"
#include "Util.h"
#include <random>

#include "Random.h"
#include "Setting.h"
#include "Singleton.h"
#include "Timer.h"

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
	//bool DepreciatedManager::isThreadEmpty()
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
	class ExecutingData : public Singleton<ExecutingData>
	{
	public:
		std::vector<service> sm_serviceArray;
		std::atomic_int8_t sm_serviceId;
		shared_mutex sm_containerMutex;
		std::atomic_uint64_t sm_waitingTaskNumber;
		std::deque<size_t> sm_executeQueue;
		std::atomic_uint sm_completedNumber;
	};
	class PoolData : public Singleton<PoolData>
	{
	public:
		std::vector<ManagerService> sm_services;
		shared_mutex sm_containerMutex;
	};
	ManagerService::ManagerService()
		:m_serviceId(ExecutingData::Get().sm_serviceId++)
	{
		m_serviceThread = std::thread([this]()
		{
			this->managerService();
		});
	}
	ManagerService::ManagerService(ManagerService&& move)noexcept
		: m_serviceId(move.m_serviceId),
		m_serviceThread(std::move(move.m_serviceThread)),
		m_termination(move.m_termination.load()),
		m_executing(move.m_executing.load()),
		m_condition(move.m_condition.load()),
		m_count(move.m_count.load())
	{}
	ManagerService& ManagerService::operator=(ManagerService&& move)noexcept
	{
		m_serviceId = move.m_serviceId;
		m_serviceThread = std::move(move.m_serviceThread); 
		m_termination = move.m_termination.load();
		m_executing = move.m_executing.load();
		m_condition = move.m_condition.load();
		m_count = move.m_count.load();
		return *this;
	}
	//通知当前线程结束，但不阻塞调用线程
	void ManagerService::terminate()
	{
		m_termination = true;
		m_threadNotifier.notify_one();
	}
	//阻塞调用线程到当前线程结束（如果没有使用Terminate则会永久阻塞）
	void ManagerService::join()
	{
		if (m_serviceThread.joinable())
			m_serviceThread.join();
	}
	//通知当前线程结束，并阻塞调用线程到当前线程结束
	void ManagerService::terminateAndJoin()
	{
		m_termination = true;
		m_threadNotifier.notify_one();
		join();
	}
	//检查当前线程是否结束
	bool ManagerService::isTerminate()
	{
		return m_termination;
	}
	//设置当前线程唤醒条件
	void ManagerService::setCondition(bool condition)
	{
		m_condition = condition;
	}
	//检查注册的条件是否成立
	bool ManagerService::isConditionHold()const
	{
		return m_condition;
	}
	//返回当前服务ID
	size_t ManagerService::getTaskId() const
	{
		return m_serviceId;
	}
	//唤醒当前线程，但如果当前线程正在执行任务，则不唤醒
	void ManagerService::notify()
	{
		//增加唤醒次数
		++m_count;
		if (!m_executing)
			m_threadNotifier.notify_one();
	}
	//以给定条件结果唤醒当前线程，但如果当前线程正在执行任务，则不唤醒
	void ManagerService::notifyWithCondition(bool condition)
	{
		++m_count;
		setCondition(condition);
		if (!m_executing)
			m_threadNotifier.notify_one();
	}
	//线程内实际执行的服务
	void ManagerService::managerService()
	{
		//初始化条件变量锁
		unique_lock conditionLock = unique_lock(m_conditionMutex);
		size_t index = 0;
		bool executingQueueEmpty = false;
		while (true)
		{
			//等待唤醒
			m_threadNotifier.wait(conditionLock, [this, &executingQueueEmpty]()
			{
				{
					read_lock lock(ExecutingData::Get().sm_containerMutex);
					executingQueueEmpty = !ExecutingData::Get().sm_executeQueue.empty();
				}
				//如果结束条件没有被设置，且任务队列不为空并且唤醒条件为真，则唤醒
				return  m_termination || (m_condition && executingQueueEmpty);
			}
			);
			if (m_termination)
			{
				break;
			}
			//若当前队列不为空，则运行
			do
			{
				m_executing = true;
				{
					//待执行任务队列的临界区
					write_lock queueLock(ExecutingData::Get().sm_containerMutex);
					//获取待执行任务ID
					index = ExecutingData::Get().sm_executeQueue.front();
					if (!ExecutingData::Get().sm_executeQueue.empty())
						ExecutingData::Get().sm_executeQueue.pop_front();
					//判断当前任务队列是否为空，如果为空则结束当前执行并继续等待。
					m_executing = m_count > 0 && !ExecutingData::Get().sm_executeQueue.empty();
					if (m_termination)
						break;
					ExecutingData::Get().sm_serviceArray[index]();
				}
			}
			while (m_executing);
		}
	}

	//void Manager::manageService()
	//{
	//	unique_lock lock = unique_lock(sm_conditionMutex);
	//	size_t index = 0;
	//	while (true)
	//	{
	//		sm_threadNotifier.wait(lock, []()
	//			{
	//				return sm_terminate || (sm_conditionFlag &&!(isEmpty()||isServiceEmpty()));
	//			}
	//		);
	//		if (sm_terminate)
	//		{
	//			break;
	//		}
	//		bool run = false;
	//		{
	//			read_lock lock(sm_containerMutex);
	//			run = !sm_executeQueue.empty();
	//		}
	//		while(run)
	//		{
	//			{
	//				write_lock queueLock(sm_containerMutex);
	//				index = sm_executeQueue.front();
	//				sm_executeQueue.pop_front();
	//				sm_conditionFlag = run = !sm_executeQueue.empty();
	//			}
	//			sm_serviceArray[index]();
	//		}
	//	}
	//}
	//添加新服务到服务队列，该函数用于子类注册服务
	void Manager::add(service&& serviceFunc)
	{
		write_lock queueLock(ExecutingData::Get().sm_containerMutex);
		ExecutingData::Get().sm_serviceArray.emplace_back(std::move(serviceFunc));
	}
	//返回是否添加新的线程到线程池
	bool Manager::allocateNewThread()
	{
		bool allocate = false;
		static seconds startTime = Timer<seconds>::Now();
		//如果规定的时间区间内完成任务数小于规定的任务数，则添加新的线程
        if (Timer<seconds>::Now() - startTime > Setting::Get().getNewThreadAllocationTime())
		{ 
			if (ExecutingData::Get().sm_completedNumber / Setting::Get().getNewThreadAllocationTime().count() > Setting::Get().getTaskPerSecond()
				&& PoolData::Get().sm_services.size() < Setting::Get().getMaxThread())
			{
				allocate =  true;
			}
            startTime = Timer<seconds>::Now();
			ExecutingData::Get().sm_completedNumber = 0;
		}
		return allocate;
	}
	bool Manager::deallocateAThread()
	{
		bool deallocate = false;
		static seconds startTime = Timer<seconds>::Now();
		if (Timer<seconds>::Now() - startTime > Setting::Get().getNewThreadAllocationTime())
		{
			if (ExecutingData::Get().sm_completedNumber / Setting::Get().getNewThreadAllocationTime().count() < (Setting::Get().getTaskPerSecond() / 2)
				&& PoolData::Get().sm_services.size() < Setting::Get().getMaxThread())
			{
				deallocate = true;
			}
			startTime = Timer<seconds>::Now();
			ExecutingData::Get().sm_completedNumber = 0;
		}
		return deallocate;
	}
	//添加新的任务到任务队列尾部
	void Manager::newTask(size_t id)
	{
		write_lock queueLock(ExecutingData::Get().sm_containerMutex);
		if (PoolData::Get().sm_services.empty()|| allocateNewThread())
			PoolData::Get().sm_services.emplace_back();
		ExecutingData::Get().sm_executeQueue.emplace_back(id);
	}
	//添加新的紧急任务到任务队列中间偏前方的位置
	void Manager::urgentTask(size_t id)
	{
		write_lock queueLock(ExecutingData::Get().sm_containerMutex);
		int index = Math::RandomInt::generate(0,
											  ExecutingData::Get().sm_executeQueue.size() / 3);
		ExecutingData::Get().sm_executeQueue.insert(ExecutingData::Get().sm_executeQueue.begin()+index,
											id);
	}
	//检查待执行任务队列是否为空
	bool Manager::isEmpty()
	{
		read_lock lock(ExecutingData::Get().sm_containerMutex);
		return ExecutingData::Get().sm_executeQueue.empty();
	}
	//检查注册服务列表是否为空
	bool Manager::isServiceEmpty()
	{
		read_lock lock(ExecutingData::Get().sm_containerMutex);
		return ExecutingData::Get().sm_serviceArray.empty();
	}
	//返回注册服务列表大小
	size_t Manager::serviceSize()
	{
		read_lock queueLock(ExecutingData::Get().sm_containerMutex);
		return ExecutingData::Get().sm_serviceArray.size();
	}
	size_t Manager::threadSize()
	{
		read_lock queueLock(ExecutingData::Get().sm_containerMutex);
        return PoolData::Get().sm_services.size();
	}
	//返回待执行任务队列大小
	size_t Manager::taskSize()
	{
		read_lock queueLock(ExecutingData::Get().sm_containerMutex);
        return ExecutingData::Get().sm_executeQueue.size();
	}
	//基类构造函数，需要子类提供线程服务函数，并将条件变量的条件函数保存在成员中
	Manager::Manager(std::function<void()>&& customService, std::function<bool()>&& condition)
		:m_condition(std::move(condition)),m_id(serviceSize())
	{
		add(std::move(customService));
	}
	//随机唤醒线程池中的一个线程
	void Manager::notify()const
	{
		read_lock lock(PoolData::Get().sm_containerMutex);
		if (bool condition = m_condition(); condition)
		{
			submit();
			PoolData::Get().sm_services[Math::RandomInt::generate(0, 100) % PoolData::Get().sm_services.size()].notifyWithCondition(condition);
		}
	}
	//随机唤醒线程池中的一个线程，并将任务作为紧急任务添加到队列中
	void Manager::notifyNow()const
	{
		if (bool condition = m_condition(); condition)
		{
			urgentTask(m_id);
			PoolData::Get().sm_services[Math::RandomInt::generate(0, 100) % PoolData::Get().sm_services.size()].notifyWithCondition(condition);
		}
	}
	//提交当前子类服务到待执行队列
	void Manager::submit()const
	{
		newTask(m_id);
	}
	void Manager::join()
	{
		write_lock lock(PoolData::Get().sm_containerMutex);
		for (auto& t : PoolData::Get().sm_services)
		{
			t.join();
		}
	}
	//判断线程池是否为空
	bool Manager::isThreadEmpty()
	{
		write_lock lock(PoolData::Get().sm_containerMutex);
		return PoolData::Get().sm_services.empty();
	}
	void Manager::terminate()
	{
		notifyTerminate();
	}
	void Manager::notifyTerminate()
	{
		write_lock lock(PoolData::Get().sm_containerMutex);
		for (auto& t : PoolData::Get().sm_services)
		{
			t.terminateAndJoin();
		}
	}
}
