//#pragma once
//#include <Token.h>
//#include <functional>
//#include <memory>
//namespace Compiler
//{
//	template<class StateType>
//	class Configuration
//	{
//		std::unique_ptr<std::unordered_map<StateType, StateType>>m_transitions;
//	public:
//		Configuration()
//            :m_transitions(nullptr)
//		{}
//		Configuration(Configuration&& move)noexcept
//			:m_transitions(std::move(move.m_transitions))
//		{
//			move.m_transitions = nullptr;
//		}
//		Configuration& operator=(Configuration&& move)noexcept
//		{
//			m_transitions = std::move(move.m_transitions);
//            move.m_transitions = nullptr;
//			return *this;
//		}
//		bool empty()
//		{
//			return m_transitions == nullptr;
//		}
//		void insert(StateType state, StateType next)
//		{
//			if (empty())
//                m_transitions = std::make_unique<std::unordered_map<StateType, StateType>>();
//			(*m_transitions)[state] = next;
//		}
//		StateType next(StateType state)
//		{
//			if (!empty()&&m_transitions->contains(state))
//				return (*m_transitions)[state](state);
//			else
//				return static_cast<StateType>(-1);
//		}
//	};
//	template<class StateType>
//	struct Automata
//	{
//		std::unordered_map<StateType, Configuration<StateType>> m_states;
//	};
//}