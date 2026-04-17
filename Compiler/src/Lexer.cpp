#include "Lexer.h"



namespace Compiler
{
	namespace States
	{ 
		class Character:public State<char, std::string_view>
		{
		public:
			std::shared_ptr<State> accept(char ch,
			                              std::string& history) final
			{
				if (TokenFunctions::IsChar(ch)
					|| TokenFunctions::IsUnderLine(ch)
					|| (TokenFunctions::IsDigit(ch) && !history.empty()))
				{
					history += ch;
					return shared_from_this();
				}
				else if (TokenFunctions::IsTerminate(ch))
					return std::make_shared<Complete>();
				else if (TokenFunctions::IsSpace(ch) 
						 || TokenFunctions::IsOperator(ch))
                    return std::make_shared<Accept>();
				else
				{
					return std::make_shared<Reject>();
				}
			}
			std::string_view name() const final
			{
				return "character";
			}
		};
		class String:public State<char, std::string_view>
		{
		public:
			std::shared_ptr<State> accept(char ch,
			                              std::string& history) final
			{
				if (TokenFunctions::IsQuote(ch))
					return std::make_shared<Accept>();
				else if (TokenFunctions::IsTerminate(ch))
					return std::make_shared<Complete>();
				else
				{
					history += ch;
					return shared_from_this();
				}

			}
			std::string_view name() const final
			{
				return "string";
			}
		};
		class Number:public State<char, std::string_view>
		{
		public:
			std::shared_ptr<State> accept(char ch,
			                              std::string& history) final
			{
				if (TokenFunctions::IsDigit(ch)
					||(ch == '.'&& !history.empty()))
				{
                    history += ch;
					return shared_from_this();
				}
				else if (TokenFunctions::IsTerminate(ch))
					return std::make_shared<Complete>();
				else if (TokenFunctions::IsSpace(ch))
                    return std::make_shared<Accept>();
				else
				{
					return std::make_shared<Reject>();
				}

			}
			std::string_view name() const final
			{
				return "number";
			}
		};
		class Operator:public State<char, std::string_view>
		{
		public:
			std::shared_ptr<State> accept(char ch,
			                              std::string& history) final
			{
				if (TokenFunctions::IsOperator(ch))
				{
                    history += ch;
					return std::make_shared<Operator>();
				}
				else if (TokenFunctions::IsTerminate(ch))
					return std::make_shared<Complete>();
				else if (TokenFunctions::IsSpace(ch)
						 || TokenFunctions::IsDigit(ch)
						 || TokenFunctions::IsUnderLine(ch)
						 || TokenFunctions::IsChar(ch))
                    return std::make_shared<Accept>();
				else
				{
					return std::make_shared<Reject>();
				}

			}
			std::string_view name() const final
			{
				return "operator";
			}
		};
		class Bracket: public State<char, std::string_view>
		{
		public:
			std::shared_ptr<State> accept(char ch,
			                              std::string& history) final
			{
				history += ch;
				return std::make_shared<Accept>();
			}
			std::string_view name() const final
			{
				return "bracket";
			}
		};
		class Default:public State<char, std::string_view>
		{
		public:
			std::shared_ptr<State> accept(char ch,
			                              std::string& history) final
			{
				if (!history.empty())
					return std::make_shared<Error>();
				else if (TokenFunctions::IsTerminate(ch))
					return std::make_shared<Complete>();
				else if (TokenFunctions::IsChar(ch) || TokenFunctions::IsUnderLine(ch))
					return std::make_shared<Character>();
				else if (TokenFunctions::IsDigit(ch))
					return std::make_shared<Number>();
				else if (TokenFunctions::IsOperator(ch))
					return std::make_shared<Operator>();
				else if (TokenFunctions::IsQuote(ch))
					return std::make_shared<String>();
				else if (TokenFunctions::IsSkipCharacter(ch))
					return std::make_shared<Default>();
				else if (TokenFunctions::IsBracket(ch))
					return std::make_shared<Bracket>();
				else
					return std::make_shared<Error>();
			}
			std::string_view name() const final
			{
				return "default";
			}
		};
	}
	
	std::unique_ptr<Token> GetTokenType(std::shared_ptr<States::State<char, std::string_view>>& init
										,std::string&& statement)
	{
		if (init->isThisState(States::Number()))
		{
			auto result = States::NumberToken::classify(statement);
			if (result->type() == TokenType::DoubleLiteral
				|| result->type() == TokenType::IntegerLiteral)
				return std::move(result);
		}
		else if (init->isThisState(States::String()))
		{
			return std::make_unique<States::StringLiteralToken>(std::move(statement));
		}
        else if (init->isThisState(States::Character()))
		{
			if (TokenFunctions::IsKeyword(statement))
                return std::make_unique<States::KeywordToken>(std::move(statement));
			else if (TokenFunctions::IsLogicalOperator(statement)
					 ||TokenFunctions::IsBinOperator(statement))
                return std::make_unique<States::OperatorToken>(std::move(statement));
            else
                return std::make_unique<States::IdentifierToken>(std::move(statement));
		}
		else if (init-> isThisState(States::Operator()))
		{
			return std::make_unique<States::OperatorToken>(std::move(statement));
		}
        else if (init->isThisState(States::Bracket()))
		{
			return std::make_unique<States::BracketToken>(std::move(statement));
		}
		return std::make_unique<States::InvalidToken>(std::move(statement));
	}
	void Lexer::tokenize(const std::string& statement)
	{
		std::shared_ptr<States::State<char, std::string_view>> defaultPtr = std::make_shared<States::Default>();
		std::shared_ptr<States::State<char, std::string_view>> init = defaultPtr;
		std::shared_ptr<States::State<char, std::string_view>> current = init;
		std::string_view name;
		std::string currentToken;
		for (size_t i = 0;;)
		{
			current = current->accept(statement[i], currentToken);
			if (init->name() == "default")
			{
				init = current;
				continue;
			}
			else
				++i;
			if (current->isThisState(States::Accept())
				|| init->isThisState(States::Complete())
				|| i >= statement.size())
			{
				auto token = GetTokenType(init, std::move(currentToken));
				currentToken.clear();
				if (token == nullptr || token->type() == TokenType::Error)
				{
					setError(ErrorCode::NotRecognizableToken, i);
					break;
				}
				m_tokens.emplace_back(std::move(token));
				if (init->isThisState(States::Complete())
					|| i >= statement.size())
					break;
				init = current = defaultPtr;
			}
			else if (init->isThisState(States::Error()))
			{
				setError(ErrorCode::InvalidCharacter, i);
				break;
			}
			else if (init->isThisState(States::Reject()))
			{
				currentToken.clear();
				--i;
			}
		}
	}
	void Lexer::reconstruct(const std::string& statement)
	{
		m_error = std::make_pair(ErrorCode::None, -1);
        m_tokens.clear();
		tokenize(statement);
	}
	//CharacterTypes Lexer::GetState(CharacterTypes init, char c)
	//{
	//	if (c == '\n'
	//		//对于一个随意的空格，在没有任何词法成分的情况下会被忽略
	//		|| (TokenFunctions::IsSpace(c) && init == CharacterTypes::None))
	//		return CharacterTypes::Skip;
	//	if (
	//		//当字符为';'/'\0'是表明语句达到结尾，为Terminate状态
	//		c == ';' || c == '\0'
	//		//当字符为' '时表明当前Token已经结束，返回Terminate。但对于字符字面量，其判断截止条件为'\"',所以可以接受' '
	//		|| (c == ' '&& init != CharacterTypes::String)
	//		//当字符为'\n'时表明语句并未结束。但对于字符字面量而言是非法的，所以表明为Terminate状态
	//		|| (c == '\n' && init == CharacterTypes::String)
	//		)
	//		return CharacterTypes::Terminate;


	//	if (TokenFunctions::IsBracket(c))
	//		return CharacterTypes::Bracket;
	//	//当传入字符为'"'时表明开始了一个字符串字面或结束了一个字符串字面量
	//	if (TokenFunctions::IsQuote(c))
	//	{
	//		//开始一个字面量
	//		return CharacterTypes::String;
	//	}

	//	//当传入字符为'a'-'z'/'A'-'Z'/'下划线'时表明当前是一个字符，返回Char
	//	if (TokenFunctions::IsChar(c)
	//		|| TokenFunctions::IsUnderLine(c)
	//		|| (init == CharacterTypes::String && c == ' '))
	//		return CharacterTypes::Char;
	//	//当传入字符为'0'-'9'时表明当前是一个数字，返回Number
	//	if (TokenFunctions::IsDigit(c))
	//		return CharacterTypes::Number;
	//	//当传入字符包含于Tokens::Operators中时表明当前是一个操作符，返回Operator
	//	if (TokenFunctions::IsOperator(c))
	//		return CharacterTypes::Operator;
	//	//对于非字面量，'\n'是可以被接受的，会被跳过。


	//	return CharacterTypes::Fail;
	//}
	//void Lexer::generateError(CharacterTypes init, size_t pos)
	//{
	//	if (init == CharacterTypes::String)
	//	{
	//		setError(ErrorCode::NotClosedStringLiteral, pos);
	//	}
	//	if (init == CharacterTypes::Operator)
	//	{
	//		setError(ErrorCode::InvalidOperator, pos);
	//	}
	//}
	//bool Lexer::isContinue(CharacterTypes init, char c, CharacterTypes current)
	//{
	//	if (init == current&& current != CharacterTypes::String)
	//		return true;
	//	else
	//	{
	//		if (c == '\n')
	//			return false;
	//		if (init == CharacterTypes::String)
	//		{
	//			if (c == '\"')
	//				return false;
	//			if (current == CharacterTypes::Char)
	//				return true;
	//		}
	//		if (init == CharacterTypes::Char)
	//		{
	//			if (current == CharacterTypes::Operator || current == CharacterTypes::Bracket)
	//			{
	//				return false;
	//			}
	//			return true;
	//		}

	//		return false;
	//	}
	//}
	//TokenType Lexer::getTokenType(CharacterTypes state, Index current, std::string& token)
	//{
	//	if (state == CharacterTypes::Char)
	//	{
	//		if (TokenFunctions::IsKeyword(token))
	//			return TokenType::Keyword;
	//		else if (TokenFunctions::IsLogicalOperator(token))
	//			return TokenType::LogicalOperator;
	//		else
	//			return TokenType::Identifier;
	//	}
	//	else if (state == CharacterTypes::Number)
	//	{
	//		return TokenType::NumberLiteral;
	//	}
	//	else if (state == CharacterTypes::Operator)
	//	{
	//		if (TokenFunctions::IsBinOperator(token))
	//			return TokenType::BinOperator;
	//		else if (TokenFunctions::IsUniOperator(token))
	//			return TokenType::UniOperator;
	//		else if (TokenFunctions::IsLogicalOperator(token))
	//			return TokenType::LogicalOperator;
	//		else
	//			return TokenType::Operator;
	//	}
	//	else if (state == CharacterTypes::String)
	//	{
	//		return TokenType::StringLiteral;
	//	}
	//	else if (state == CharacterTypes::Bracket)
	//	{
	//		if (token == "(")
	//			return TokenType::LeftBracket;
	//		else if (token == "[")
 //               return TokenType::LeftSquare;
 //           else if (token == "{")
 //               return TokenType::LeftCurly;
 //           else if (token == "]")
 //               return TokenType::RightSquare;
 //           else if (token == "}")
 //               return TokenType::RightCurly;
	//		else
	//			return TokenType::RightBracket;
	//	}

	//	return TokenType::Error;
	//}
	//void Lexer::tokenize(const std::string& statement)
	//{
	//	if (statement.empty())
	//	{
	//		setError(ErrorCode::NotAValidStatement, 0);
	//		return;
	//	}
	//	CharacterTypes init = CharacterTypes::None, current = CharacterTypes::None;
	//	std::string token;
	//	char character;
	//	bool isQuoteClosed, requireSpace = false;
	//	for (Index n = 0; n < statement.size();)
	//	{

	//		init = GetState(init, statement[n++]);
	//		if (init != CharacterTypes::String)
	//			token = statement[n-1];
	//		isQuoteClosed = false;
	//		if (init == CharacterTypes::Skip)
	//		{
	//			requireSpace = false;
	//			continue;
	//		}

	//		if (init == CharacterTypes::Terminate || init == CharacterTypes::Fail)
	//			break;
	//		if (requireSpace)
	//		{
	//			setError(ErrorCode::IdentifierFormatError, static_cast<long long>(n - 1));
	//			break;
	//		}

	//		while (init != CharacterTypes::Bracket
	//			   && init != CharacterTypes::Fail
	//			   && current != CharacterTypes::Fail
	//			   && current != CharacterTypes::Terminate)
	//		{
	//			character = statement[n];
	//			current = GetState(init, character);
	//			if (current == CharacterTypes::Skip)
	//			{
	//				if (n < statement.size())
	//					++n;
	//				continue;
	//			}
	//			else if (current == CharacterTypes::Terminate)
	//			{
	//				if (n < statement.size() && character != ';')
	//					++n;
	//				break;
	//			}
	//			else if (current == CharacterTypes::Fail)
	//			{
	//				//设置字符格式错误
	//				setError(ErrorCode::InvalidCharacter, static_cast<long long>(n));
	//				break;
	//			}
	//			else if (init == CharacterTypes::Number && current == CharacterTypes::Char)
	//			{
	//				setError(ErrorCode::InvalidNumberFormat, n);
	//				current = CharacterTypes::Fail;
	//				break;
	//			}
	//			if (current == CharacterTypes::String)
	//			{
	//				isQuoteClosed = true;
	//				requireSpace = true;
	//			}

	//			if (!isContinue(init, character, current))
	//			{
	//				if (init == CharacterTypes::String && !isQuoteClosed)
	//				{
	//					setError(ErrorCode::NotClosedStringLiteral, static_cast<long long>(n));
	//				}
	//				++n;
	//				break;
	//			}

	//			token += character;
	//			++n;
	//			if (token == "\"\"")
	//				break;
	//			//没有长度超过3的运算符
	//			if (current == CharacterTypes::Operator && token.size() > 2)
	//			{
	//				//设置操作符格式错误
	//				setError(ErrorCode::OperatorFormatError, static_cast<long long>(n));
	//				break;
	//			}
	//		}
	//		//
	//		if (init == CharacterTypes::Fail
	//			|| current == CharacterTypes::Fail)
	//		{
	//			return;
	//		}
	//		m_tokens.emplace_back(getTokenType(init, n, token), m_rawTokens.size());
	//		m_rawTokens.emplace_back(token);
	//		init = current = CharacterTypes::None;
	//		token = "";

	//	}
	//	if (!isError())
	//	{
	//		if (m_rawTokens.size() == 1)
	//			setError(ErrorCode::NotAValidStatement, statement.size());
	//		else if (m_rawTokens.empty())
	//			setError(ErrorCode::EmptyStatement, statement.size());
	//	}

	//}
	Lexer::Lexer()
		:m_error(ErrorCode::None, -1)
	{
		
	}
	Lexer::Lexer(const std::string& statement)
	{
		reconstruct(statement);
	}
	Lexer::Lexer(std::string&& statement)
	{
		reconstruct(std::move(statement));
	}
	Lexer::Lexer(Lexer&& move)noexcept
		:m_error(move.m_error), m_tokens(std::move(move.m_tokens))
	{
		move.m_error = std::make_pair(ErrorCode::None, -1);
		move.m_tokens.clear();
	}
	const TokenList& Lexer::getTokens()const
	{
		return m_tokens;
	}
	TokenList&& Lexer::moveTokens()
	{
		return std::move(m_tokens);
	}
	bool Lexer::isError()const
	{
		return m_error.first != ErrorCode::None
		|| m_tokens.empty();
	}
	size_t Lexer::tokenSize()const
	{
		return m_tokens.size();
	}
	long long Lexer::getErrorPosition()const
	{
		return m_error.second;
	}

	ErrorCode Lexer::getErrorCode() const
	{
		return m_error.first;
	}
	const TokenError& Lexer::getError() const
	{
		return m_error;
	}
	void Lexer::setError(ErrorCode error, long long errorPosition)
	{
		m_error = std::make_pair(error, errorPosition);
	}
}
