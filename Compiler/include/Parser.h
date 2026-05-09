#pragma once
#include <functional>
#include <TokenStates.h>

namespace Compiler
{
	enum class CharacterTypes:char
	{
		Fail=-1,
		None,
		Skip,
		Terminate,
		Char,//Keyword/Identifier/Literal
		Number,//NumberLiteral
		String,//StringLiteral
		Bracket,
		Operator,
	};



	class Parser
	{
		TokenList m_tokens;
		TokenError m_error;
		using ParserState = States::State<char, std::string_view>;
		using ParserStatePtr = std::shared_ptr<ParserState>;

		void errorHandler(ParserStatePtr& init, ParserStatePtr& current, size_t position);
		//分词自动机
		void tokenize(const std::string& statement);
		//获取当前字符读取状态
		//判断是否分词
		//获取Token类型
		//生成Token规则错误

	public:
		Parser();
		Parser(std::string&& statement);
		Parser(Parser&& move)noexcept;
		//获取Token元素分类和该Token在原文列表中的位置的列表
		const TokenList& getTokens()const;
		[[nodiscard]]
		TokenList&& moveTokens();
		//获取Token原文列表
		//检查是否出现Token规则错误
		bool isError()const;
		//移动当前位置的词素字符
		//返回Token数量
		size_t tokenSize()const;
		//返回Token原文数量
		//获取Token规则错误位置
        long long getErrorPosition()const;
        //获取Token规则错误类型
		ErrorCode getErrorCode() const;
		const TokenError& getError() const;
		//重新构造词法分析器
		void reconstruct(const std::string& statement);
		//设置Token规则错误
		void setError(ErrorCode error, long long errorPosition);
	};
}
