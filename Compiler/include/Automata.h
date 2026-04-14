#pragma once
#include <Token.h>
#include <functional>
namespace Compiler
{
	enum class TransitionAction
	{
		Fail = -1,
		Stay,
		Move,
		Finish
	};
	//template<class StateType>
	//class Configuration
	//{
	//	std::function<TransitionAction()> m_predicate;
	//	StateType m_next;
	//public:
	//	Configuration(StateType next, std::function<TransitionAction()>&& function)noexcept
	//		:m_predicate(std::move(function)), m_next(next)
	//	{
	//	}
	//	Configuration(const Configuration& config) noexcept
	//		:m_predicate(config.m_predicate), m_next(config.m_next)
	//	{
	//	}
	//	Configuration(Configuration&& config) noexcept
	//		:m_predicate(std::move(config.m_predicate)), m_next(config.m_next)
	//	{
	//	}
	//	TransitionAction next()const
	//	{
	//		return m_predicate();
	//	}
	//	StateType get()const
	//	{
	//		return m_next;
	//	}
	//	Configuration& operator=(const Configuration& config)noexcept
	//	{
	//		m_next = config.m_next;
	//		m_predicate = config.m_predicate;
	//		return *this;
	//	}
	//	Configuration& operator=(Configuration&& config)noexcept
	//	{
	//		m_next = config.m_next;
	//		m_predicate = std::move(config.m_predicate);
	//		return *this;
	//	}
	//};
	template<class StateType, class EvaluateType>
	class Automata
	{
		std::unordered_map<StateType,  std::function<StateType(EvaluateType)>> m_stateMap;
	public:

		void bind(StateType init, const std::function<StateType(EvaluateType)>& transition)
		{
			m_stateMap[init] = transition;
		}
		void bind(StateType init, std::function<StateType(EvaluateType)>&& transition)
		{
			m_stateMap[init] = std::move(transition);
		}
		bool contains(StateType init)
		{
			return m_stateMap.contains(init);
		}
		auto transit(StateType init)
		{
			if (!contains(init))
				return static_cast<StateType>(-1);
			return m_stateMap[init]();
		}
	};
}