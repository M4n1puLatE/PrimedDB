#pragma once
#include <Manager.h>
#include <Singleton.h>
#include <queue>
#include <Error.h>

namespace ErrorHandler
{
	class ErrorManager final:public Util::Singleton<ErrorManager>,public Util::Manager
	{
		THIS_IS_SINGLETON;
		std::queue<Error> m_errorQueue;
		std::shared_mutex m_mutex;
		std::atomic_uint32_t m_id;

		ErrorManager();
	public:
		uint32_t getId();
	};
}
