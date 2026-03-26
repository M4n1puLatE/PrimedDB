#pragma once
#include <Token.h>

namespace Compiler
{
	enum class CharStates:unsigned char
	{
		None,
		Error,
		Skip,
		Terminate,
		Char,//Keyword/Identifier/Literal
		Number,//NumberLiteral
		String,//StringLiteral
		Bracket,
		Operator,
	};

	class Lexer
	{
		TokenList m_tokens;
		StringList m_rawTokens;
		TokenError m_error;
		//分词自动机
		void tokenize(const std::string& statement);
		//获取当前字符读取状态
		static CharStates GetState(CharStates init,char c);
		//判断是否分词
		static bool isContinue(CharStates init, char c,CharStates current);
		//获取Token类型
		TokenType getTokenType(CharStates state, Index current ,std::string& token);
		//生成Token规则错误
		void generateError(CharStates init, size_t pos);
	public:
		Lexer();
		Lexer(const std::string& statement);
		Lexer(std::string&& statement);
		Lexer(Lexer&& move)noexcept;
		//获取Token元素分类和该Token在原文列表中的位置的列表
		const TokenList& getTokens()const;
		//获取Token原文列表
		const StringList& getRawTokens()const;
		//检查是否出现Token规则错误
		bool isError()const;
		//移动当前位置的词素字符
		std::string&& moveAt(size_t index);
		//返回Token数量
		size_t tokenSize()const;
		//返回Token原文数量
        size_t rawTokenSize()const;
		//获取Token规则错误位置
        long long getErrorPosition()const;
        //获取Token规则错误类型
		ErrorCode getErrorCode()const;
		const TokenError& getError() const;
		//重新构造词法分析器
		void reconstruct(const std::string& statement);
		//设置Token规则错误
		void setError(ErrorCode errorCode, long long errorPosition);
	};
}
