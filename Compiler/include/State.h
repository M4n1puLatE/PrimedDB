#pragma once
#include <memory>
#include <string>
#include <string_view>

namespace Compiler::States
{
	enum class TransitionActions:char
	{
		Fail = -1,
		None,
        Stay,
        Move,
		Finish,
	};
	template <class ItemType,class IdentifyType>
	class State:public std::enable_shared_from_this<State<ItemType,IdentifyType>>
	{
	public:
		virtual std::shared_ptr<State> accept(ItemType ch,
		                                      std::string& history) = 0;
		virtual IdentifyType name() const = 0;
		template <class T>
		requires std::is_base_of_v<State, T>
		static std::unique_ptr<State> Create()
		{
			return std::make_unique<T>();
		}
		bool isThisState(const State& state)const
		{
			return state.name() == this->name();
		}
		static bool SameState(const std::shared_ptr<State>& first, const std::shared_ptr <State>& second)
		{
			return first->name() == second->name();
		}
        ~State() = default;
	};
	
	class Reject:public State<char,std::string_view>
	{
	public:
		Reject() = default;
		std::shared_ptr<State> accept(char ch,
		                              std::string& history) final;
		std::string_view name() const final;
	};
	class Complete: public State<char, std::string_view>
	{
	public:
		Complete() = default;
		std::shared_ptr<State> accept(char ch,
		                              std::string& history) final;
        std::string_view name() const final;
	};
	class Error: public State<char, std::string_view>
	{
	public:
		Error() = default;
		std::shared_ptr<State> accept(char ch,
		                              std::string& history) final;
		std::string_view name() const override;
	};
	class Accept:public State<char, std::string_view>
	{
	public:
		Accept() = default;
		std::shared_ptr<State> accept(char ch,
		                              std::string& history) final;
		std::string_view name() const final;
	};
}
