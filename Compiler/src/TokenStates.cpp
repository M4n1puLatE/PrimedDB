#include <TokenStates.h>
namespace Compiler::States {
///////////////////////////////////////////////////////////////
///
///							Token
///
///////////////////////////////////////////////////////////////
	bool Token::valid(std::string_view)const
	{
		return true;
	}
	bool Token::equals(const Token& token) const
	{
		return type() == token.type();
	}
	bool Token::operator==(const Token& token) const
	{
		return equals(token);
	}

	///////////////////////////////////////////////////////////////
	///
	///						InvalidToken
	///
	///////////////////////////////////////////////////////////////
	TokenType InvalidToken::type() const override
	{
		return TokenType::Error;
	}
	const std::string& InvalidToken::get()const
	{
		return m_error;
	}
	InvalidToken::InvalidToken(std::string&& move)
		: m_error(std::move(move))
	{
		
	}
	bool InvalidToken::valid(std::string_view any)const
	{
		return false;
	}
	
///////////////////////////////////////////////////////////////
///
///					IdentifierToken
///
///////////////////////////////////////////////////////////////
	IdentifierToken::IdentifierToken(std::string&& identifier)noexcept
		: m_identifier(std::move(identifier))
	{
		
	}
	IdentifierToken::IdentifierToken(IdentifierToken&& move)noexcept
        : m_identifier(std::move(move.m_identifier))
	{
		
	}
	TokenType IdentifierToken::type() const override
	{
		return TokenType::Identifier;
	}
	std::string_view IdentifierToken::get() const
	{
		return m_identifier;
	}
	IdentifierToken& IdentifierToken::operator=(IdentifierToken&& move)noexcept
	{
        m_identifier = std::move(move.m_identifier);
		return *this;
	}
///////////////////////////////////////////////////////////////
///
///					  NumberToken
///
///////////////////////////////////////////////////////////////
	std::unique_ptr<Token> NumberToken::classify(const std::string& token)
	{
		try
		{
			int value = std::stoi(token);
			return std::make_unique<IntegerToken>(value);
		}
		catch (const std::invalid_argument& e)
		{
			try
			{
				double value = std::stod(token);
				return std::make_unique<DoubleToken>(value);
			}
			catch (const std::invalid_argument& e)
			{
				return nullptr;
			}
		}
	}
	IntegerToken::IntegerToken(long long data)noexcept
		: m_integer(data)
	{}
	IntegerToken::IntegerToken(IntegerToken&& move)noexcept
        :m_integer(move.m_integer)
	{}
	TokenType IntegerToken::type() const override
	{
		return TokenType::IntegerLiteral;
	}
	long long IntegerToken::get() const
	{
		return m_integer;
	}
	IntegerToken& IntegerToken::operator=(IntegerToken&& move)noexcept
	{
		m_integer = move.m_integer;
		return *this;
	}
	DoubleToken::DoubleToken(double data)noexcept
		: m_double(data)
	{
		
	}
	DoubleToken::DoubleToken(DoubleToken&& move)noexcept
        : m_double(move.m_double)
	{
		
	}
	TokenType DoubleToken::type() const override
	{
		return TokenType::DoubleLiteral;
	}
	double DoubleToken::get() const
	{
		return m_double;
	}
	DoubleToken& DoubleToken::operator=(DoubleToken&& move)noexcept
	{
		m_double = move.m_double;
        return *this;
	}
///////////////////////////////////////////////////////////////
///
///						KeywordToken
///
///////////////////////////////////////////////////////////////
///
    TokenType getKeywordType(std::string_view keyword)
    {
        if (keyword == "select") return TokenType::Select;
        else if (keyword == "from") return TokenType::From;
        else if (keyword == "insert") return TokenType::Insert;
        else if (keyword == "where") return TokenType::Where;
        else if (keyword == "into") return TokenType::Into;
        else if (keyword == "join") return TokenType::Join;
        else if (keyword == "table") return TokenType::Table;
        else if (keyword == "create") return TokenType::Create;
        else if (keyword == "delete") return TokenType::Delete;
        else if (keyword == "update") return TokenType::Update;
        else if (keyword == "set") return TokenType::Set;
        else if (keyword == "values") return TokenType::Values;
        else if (keyword == "alter") return TokenType::Alter;
        else if (keyword == "drop") return TokenType::Drop;
        else if (keyword == "truncate") return TokenType::Truncate;
        else if (keyword == "group") return TokenType::Group;
        else if (keyword == "order") return TokenType::Order;
        else if (keyword == "by") return TokenType::By;
        else if (keyword == "asc") return TokenType::Asc;
        else if (keyword == "desc") return TokenType::Desc;
        else if (keyword == "count") return TokenType::Count;
        else if (keyword == "sum") return TokenType::Sum;
        else if (keyword == "avg") return TokenType::Avg;
        else if (keyword == "max") return TokenType::Max;
        else if (keyword == "min") return TokenType::Min;
        else if (keyword == "distinct") return TokenType::Distinct;
        else if (keyword == "having") return TokenType::Having;
        else if (keyword == "as") return TokenType::As;
        else if (keyword == "on") return TokenType::On;
        else if (keyword == "use") return TokenType::Use;
        else if (keyword == "primary") return TokenType::Primary;
        else if (keyword == "foreign") return TokenType::Foreign;
        else if (keyword == "key") return TokenType::Key;
        else if (keyword == "unique") return TokenType::Unique;
        else if (keyword == "series") return TokenType::Series;
        else if (keyword == "null") return TokenType::Null;
        else if (keyword == "default") return TokenType::Default;
        else if (keyword == "between") return TokenType::Between;
        else if (keyword == "like") return TokenType::Like;
        else if (keyword == "in") return TokenType::In;
        else if (keyword == "exists") return TokenType::Exists;
        else if (keyword == "case") return TokenType::Case;
        else if (keyword == "when") return TokenType::When;
        else if (keyword == "then") return TokenType::Then;
        else if (keyword == "else") return TokenType::Else;
        else if (keyword == "end") return TokenType::End;
        else if (keyword == "is") return TokenType::Is;
        else if (keyword == "any") return TokenType::Any;
        else if (keyword == "all") return TokenType::All;
        else if (keyword == "some") return TokenType::Some;
        else if (keyword == "true") return TokenType::True;
        else if (keyword == "false") return TokenType::False;
        else if (keyword == "date") return TokenType::Date;
        else if (keyword == "time") return TokenType::Time;
        else if (keyword == "user") return TokenType::User;
        else return TokenType::Error; // 如果没有匹配，可能是普通标识符
    }
	void KeywordToken::categorize(std::string_view keyword)
	{
		m_type = getKeywordType(keyword);
	}
	KeywordToken::KeywordToken(std::string_view keyword)noexcept
	{
		categorize(keyword);
	}
	bool KeywordToken::valid(std::string_view token)const
	{
		return m_type != TokenType::Error&&TokenFunctions::IsKeyword(token);
	}
	TokenType KeywordToken::type() const override
	{
		return m_type;
	}
///////////////////////////////////////////////////////////////
///
///					 StringLiteralToken
///
///////////////////////////////////////////////////////////////

	StringLiteralToken::StringLiteralToken(std::string&& literal)noexcept
		: m_literal(std::move(literal))
	{
		
	}
	StringLiteralToken::StringLiteralToken(StringLiteralToken&& move)noexcept
		:m_literal(std::move(move.m_literal))
	{
		
	}
	TokenType StringLiteralToken::type() const override
	{
		return TokenType::StringLiteral;
	}
	const std::string& StringLiteralToken::get() const
	{
		return m_literal;
	}
	StringLiteralToken& StringLiteralToken::operator=(StringLiteralToken&& move)noexcept
	{
		m_literal = std::move(move.m_literal);
        return *this;
	}

///////////////////////////////////////////////////////////////
///
///						OperatorToken
///
///////////////////////////////////////////////////////////////
	void OperatorToken::categorize(std::string_view operatorl)
	{
		if (TokenFunctions::IsBinOperator(operatorl))
		{
			if (operatorl == ":=")
                m_type = TokenType::Assign;
			if (operatorl == "%")
				m_type = TokenType::Mod;
			if (operatorl == "+")
				m_type = TokenType::Add;
			if (operatorl == "-")
				m_type = TokenType::Sub;
			if (operatorl == "*")
				m_type = TokenType::Mul;
			if (operatorl == "/")
				m_type = TokenType::Div;
			if (operatorl == "**")
				m_type = TokenType::Pow;
			if (operatorl == "&&")
				m_type = TokenType::And;
			if (operatorl == "||")
				m_type = TokenType::Or;
			if (operatorl == "!")
				m_type = TokenType::Not;
			if (operatorl == "==")
				m_type = TokenType::Equal;
			if (operatorl == "&")
				m_type = TokenType::BitAnd;
			if (operatorl == "|")
				m_type = TokenType::BitOr;
			if (operatorl == "!=")
				m_type = TokenType::NotEqual;
			if (operatorl == ">")
				m_type = TokenType::Greater;
			if (operatorl == "<")
				m_type = TokenType::Less;
			if (operatorl == ">=")
				m_type = TokenType::GreaterEqual;
			if (operatorl == "<=")
				m_type = TokenType::LessEqual;
			if (operatorl == ".")
				m_type = TokenType::Dot;
			if (operatorl == "?")
				m_type = TokenType::Condition;
			if (operatorl == "union")
				m_type = TokenType::Union;
			if (operatorl == "intersect")
				m_type = TokenType::Intersect;
			if (operatorl == "minus")
				m_type = TokenType::Minus;
			if (operatorl == "+=")
				m_type = TokenType::AddAssign;
			if (operatorl == "-=")
				m_type = TokenType::SubAssign;
			if (operatorl == "*=")
				m_type = TokenType::MulAssign;
			if (operatorl == "/=")
				m_type = TokenType::DivAssign;
			if (operatorl == "%=")
				m_type = TokenType::ModAssign;
			if (operatorl == "++")
				m_type = TokenType::Pp;
			if (operatorl == "--")
				m_type = TokenType::Mm;
			if (operatorl == "^")
                m_type = TokenType::Pow;
			
		}
		else if (TokenFunctions::IsUniOperator(operatorl))
		{
			if (operatorl == "++")
                m_type = TokenType::Pp;
            if (operatorl == "--")
                m_type = TokenType::Mm;
            if (operatorl == "!")
                m_type = TokenType::Emphasize;
            if (operatorl == "?")
                m_type = TokenType::What;
		}
		else if (TokenFunctions::IsLogicalOperator(operatorl))
		{
			if (operatorl=="=")
                m_type = TokenType::Equal;
            if (operatorl=="<")
                m_type = TokenType::Less;
            if (operatorl==">")
                m_type = TokenType::Greater;
            if (operatorl=="<=")
                m_type = TokenType::LessEqual;
            if (operatorl==">=")
                m_type = TokenType::GreaterEqual;
            if (operatorl=="!=")
                m_type = TokenType::NotEqual;
			if (operatorl == "and")
                m_type = TokenType::And;
            if (operatorl == "or")
                m_type = TokenType::Or;
            if (operatorl == "not")
                m_type = TokenType::Not;
            if (operatorl == "xor")
                m_type = TokenType::Xor;
		}
		m_type = TokenType::Error;
	}
	OperatorToken::OperatorToken(std::string_view operatorl) noexcept
	{
		categorize(operatorl);
	}
	bool OperatorToken::valid(std::string_view operatorl)const override
	{
		return m_type != TokenType::Error && 
			(TokenFunctions::IsBinOperator(operatorl)
		||TokenFunctions::IsLogicalOperator(operatorl)
		||TokenFunctions::IsUniOperator(operatorl));
	}
	TokenType OperatorToken::type() const
    {
        return m_type;
    }
	void BracketToken::categorize(std::string_view bracket)
	{
		if (bracket == "(")
            m_type = TokenType::LeftBracket;
        if (bracket == ")")
            m_type = TokenType::RightBracket;
        if (bracket == "{")
            m_type = TokenType::LeftCurly;
        if (bracket == "}")
            m_type = TokenType::RightCurly;
        if (bracket == "[")
            m_type = TokenType::LeftSquare;
        if (bracket == "]")
            m_type = TokenType::RightSquare;
		m_type = TokenType::Error;
	}
	BracketToken::BracketToken(std::string_view bracket) noexcept
	{
		categorize(bracket);
	}
	bool BracketToken::valid(std::string_view token)const override
	{
		return !token.empty()&&TokenFunctions::IsBracket(token[0]);
	}
	TokenType BracketToken::type() const override
	{
		return m_type;
	}
	void BracketToken::close()
	{
		m_isOpen = false;
	}
}