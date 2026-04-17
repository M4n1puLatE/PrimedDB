#include <State.h>

namespace Compiler::States
{
	std::shared_ptr<State<char,std::string_view>> Reject::accept(char ch,
	                                                             std::string& history)
	{
        return std::make_shared<Reject>();
	}
	std::string_view Reject::name() const 
	{
		return "reject";
	}

	std::shared_ptr<State<char, std::string_view>> Complete::accept(char ch,
	                                                                std::string& history)
	{
		return std::make_shared<Complete>();
	}
	std::string_view Complete::name() const 
	{
        return "complete";
	}

	std::shared_ptr<State<char, std::string_view>> Error::accept(char ch,
	                                                             std::string& history)
	{
		return std::make_shared<Complete>();
	}
	std::string_view Error::name() const 
	{
		return "error";
	}

	std::shared_ptr<State<char, std::string_view>> Accept::accept(char ch,
	                                                              std::string& history)
	{
		return std::make_shared<Accept>();
	}
	std::string_view Accept::name() const 
	{
		return "accept";
	}
}
