#pragma once
#include <stdexcept>

#include "State.h"
#include "Token.h"
namespace Compiler::States
{
	class Token
	{
	protected:
		Token()=default;
	public:
		~Token() = default;
		virtual TokenType type() const = 0;
		virtual bool valid(std::string_view)const;
		bool equals(const Token& token) const;
		bool operator==(const Token& token) const;
	};
	class InvalidToken : public Token
	{
		std::string m_error;
	public:
		using Token::Token;
		InvalidToken(std::string&&);
		InvalidToken(InvalidToken&&) = default;
		bool valid(std::string_view)const final;
		TokenType type() const override;
		const std::string& get()const;
		InvalidToken& operator=(InvalidToken&&) = default;
	};
	class IdentifierToken : public Token
	{
		std::string m_identifier;
	public:
		IdentifierToken(std::string&& identifier)noexcept;
		IdentifierToken(IdentifierToken&& move)noexcept;
		TokenType type() const override;
        std::string_view get() const;
		IdentifierToken& operator=(IdentifierToken&& move)noexcept;
	};
	class IntegerToken: public Token
	{
		long long m_integer;
	public:
		IntegerToken(long long data)noexcept;
		IntegerToken(IntegerToken&& move)noexcept;
		TokenType type() const override;
		long long get() const;
		IntegerToken& operator=(IntegerToken&& move)noexcept;
	};
	class DoubleToken: public Token
	{
		double m_double;
	public:
		DoubleToken(double data)noexcept;
		DoubleToken(DoubleToken&& move)noexcept;
		TokenType type() const override;
		double get() const;
		DoubleToken& operator=(DoubleToken&& move)noexcept;
	};
	class NumberToken
	{
	public:
		static std::unique_ptr<Token> classify(const std::string& token);
	};
	class KeywordToken: public Token
	{
		TokenType m_type;
		void categorize(std::string_view keyword);
	public:
		KeywordToken(std::string_view keyword)noexcept;
		bool valid(std::string_view)const override;
		TokenType type() const override;
	};
	
	class StringLiteralToken: public Token
	{
		std::string m_literal;
	public:
		StringLiteralToken(std::string&& literal)noexcept;
		StringLiteralToken(StringLiteralToken&& move)noexcept;
		TokenType type() const override;
		const std::string& get() const;
		StringLiteralToken& operator=(StringLiteralToken&& move)noexcept;
	};

	class OperatorToken: public Token
	{
		TokenType m_type;
		void categorize(std::string_view operatorl);
	public:
		OperatorToken(std::string_view operatorl) noexcept;
        bool valid(std::string_view)const override;
		TokenType type() const override;
	};
	class BracketToken: public Token
	{
		TokenType m_type;
		bool m_isOpen=true;
		void categorize(std::string_view bracket);
	public:
		BracketToken(std::string_view bracket) noexcept;
		bool valid(std::string_view)const override;
		TokenType type() const override;
		void close();
	};

	class ClassifyToken
	{
	public:
		static std::unique_ptr<Token> Classify(std::string_view token);
	};
	
}
