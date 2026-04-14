#include "Parser.h"

namespace Compiler
{
    TokenType Parser::GetKeyword(const std::string& token)
    {
        if (token == "SELECT" || token == "select") return TokenType::Select;
        else if (token == "FROM" || token == "from") return TokenType::From;
        else if (token == "INSERT" || token == "insert") return TokenType::Insert;
        else if (token == "WHERE" || token == "where") return TokenType::Where;
        else if (token == "INTO" || token == "into") return TokenType::Into;
        else if (token == "JOIN" || token == "join") return TokenType::Join;
        else if (token == "TABLE" || token == "table") return TokenType::Table;
        else if (token == "CREATE" || token == "create") return TokenType::Create;
        else if (token == "DELETE" || token == "delete") return TokenType::Delete;
        else if (token == "UPDATE" || token == "update") return TokenType::Update;
        else if (token == "SET" || token == "set") return TokenType::Set;
        else if (token == "VALUES" || token == "values") return TokenType::Values;
        else if (token == "ALTER" || token == "alter") return TokenType::Alter;
        else if (token == "DROP" || token == "drop") return TokenType::Drop;
        else if (token == "TRUNCATE" || token == "truncate") return TokenType::Truncate;
        else if (token == "GROUP" || token == "group") return TokenType::Group;
        else if (token == "ORDER" || token == "order") return TokenType::Order;
        else if (token == "BY" || token == "by") return TokenType::By;
        else if (token == "ASC" || token == "asc") return TokenType::Asc;
        else if (token == "DESC" || token == "desc") return TokenType::Desc;
        else if (token == "COUNT" || token == "count") return TokenType::Count;
        else if (token == "SUM" || token == "sum") return TokenType::Sum;
        else if (token == "AVG" || token == "avg") return TokenType::Avg;
        else if (token == "MAX" || token == "max") return TokenType::Max;
        else if (token == "MIN" || token == "min") return TokenType::Min;
        else if (token == "DISTINCT" || token == "distinct") return TokenType::Distinct;
        else if (token == "HAVING" || token == "having") return TokenType::Having;
        else if (token == "AS" || token == "as") return TokenType::As;
        else if (token == "ON" || token == "on") return TokenType::On;
        else if (token == "USE" || token == "use") return TokenType::Use;
        else if (token == "PRIMARY" || token == "primary") return TokenType::Primary;
        else if (token == "FOREIGN" || token == "foreign") return TokenType::Foreign;
        else if (token == "KEY" || token == "key") return TokenType::Key;
        else if (token == "UNIQUE" || token == "unique") return TokenType::Unique;
        else if (token == "SERIES" || token == "series") return TokenType::Series;
        else if (token == "NULL" || token == "null") return TokenType::Null;
        else if (token == "DEFAULT" || token == "default") return TokenType::Default;
        else if (token == "BETWEEN" || token == "between") return TokenType::Between;
        else if (token == "LIKE" || token == "like") return TokenType::Like;
        else if (token == "IN" || token == "in") return TokenType::In;
        else if (token == "EXISTS" || token == "exists") return TokenType::Exists;
        else if (token == "CASE" || token == "case") return TokenType::Case;
        else if (token == "WHEN" || token == "when") return TokenType::When;
        else if (token == "THEN" || token == "then") return TokenType::Then;
        else if (token == "ELSE" || token == "else") return TokenType::Else;
        else if (token == "END" || token == "end") return TokenType::End;
        else if (token == "IS" || token == "is") return TokenType::Is;
        else if (token == "ANY" || token == "any") return TokenType::Any;
        else if (token == "ALL" || token == "all") return TokenType::All;
        else if (token == "SOME" || token == "some") return TokenType::Some;
        else if (token == "TRUE" || token == "true") return TokenType::True;
        else if (token == "FALSE" || token == "false") return TokenType::False;
        else if (token == "DATE" || token == "date") return TokenType::Date;
        else if (token == "TIME" || token == "time") return TokenType::Time;
        else if (token == "USER" || token == "user") return TokenType::User;
        else if (token == "LRK"|| token == "lrk")return TokenType::Lrk;
        else if (token == "BXY" || token == "bxy") return TokenType::Bxy;
        return TokenType::None; // 没有匹配
    }
    TokenType Parser::GetBinOperator(const std::string& token)
    {
        if (token == "+")
            return TokenType::Add;
        else if (token == "-")
            return TokenType::Sub;
        else if (token == "*")
            return TokenType::Mul;
        else if (token == "/")
            return TokenType::Div;
        else if (token == "%")
            return TokenType::Mod;
        else if (token == "^")
            return TokenType::Pow;
        else if (token == ":=")
            return TokenType::Assign;
        else if (token == ".")
            return TokenType::Dot;
        else if (token == "&")
            return TokenType::BitAnd;
        else if (token == "|")
            return TokenType::BitOr;
        else if (token == "+=")
            return TokenType::AddAssign;
        else if (token == "-=")
            return TokenType::SubAssign;
        else if (token == "*=")
            return TokenType::MulAssign;
        else if (token == "/=")
            return TokenType::DivAssign;
        else if (token == "%=")
            return TokenType::ModAssign;

        return TokenType::None;
    }
    TokenType Parser::GetUniOperator(const std::string& token)
    {
        if (token == "++")
            return TokenType::Pp;
        else if (token == "--")
            return TokenType::Mm;
        else if (token == "!")
            return TokenType::Emphasize;
        else if (token == "?")
            return TokenType::What;
        return TokenType::None;
    }
    TokenType Parser::GetLogicalOperator(const std::string& token)
    {
        if (token == "AND" || token == "and")
            return TokenType::And;
        else if (token == "OR" || token == "or")
            return TokenType::Or;
        else if (token == "NOT" || token == "not")
            return TokenType::Not;
        else if (token == "XOR" || token == "xor")
            return TokenType::Xor;
        else if (token == "=")
            return TokenType::Equal;
        else if (token == "<")
            return TokenType::Less;
        else if (token == ">")
            return TokenType::Greater;
        else if (token == "<=")
            return TokenType::LessEqual;
        else if (token == ">=")
            return TokenType::GreaterEqual;
        else if (token == "!=")
            return TokenType::NotEqual;


        return TokenType::None;
    }
    const ParsingList& Parser::getList()const
    {
        return m_list;
    }
    const Lexer& Parser::getLexer()const
    {
        return m_lexer;
    }
    const TokenError& Parser::getError()const
    {
        return m_lexer.getError();
    }
    Parser::Parser(const std::string& statement)
        : m_lexer(statement)
    {
        
    }
    Parser::Parser(std::string&& statement)
        : m_lexer(std::move(statement))
    {
        
    }
    Parser::Parser(Lexer&& lexer)
        : m_lexer(std::move(lexer))
    {
        
    }
    Parser::Parser(Parser&& move) noexcept
        : m_lexer(std::move(move.m_lexer)), m_list(std::move(move.m_list))
    {
        
    }
    bool operateBracketStack(std::stack<TokenType>& stack, TokenType current)
    {
        if (current == TokenType::LeftBracket
            ||current == TokenType ::LeftCurlyBracket
            ||current == TokenType::LeftParenthesis)
        {
            stack.push(current);
        }
        else if (current == TokenType::RightParenthesis)
        {
            auto s = stack.top();
            if (s != TokenType::LeftParenthesis)
                return false;
            
        }
        else if (current == TokenType::RightBracket)
        {
            auto s = stack.top();
            if (s != TokenType::LeftBracket)
                return false;
        }
        else if (current == TokenType::RightCurlyBracket)
        {
            auto s = stack.top();
            if (s != TokenType::LeftCurlyBracket)
                return false;
        }
        return true;
    }
    void Parser::parse()
    {
        auto& tokenList = m_lexer.getRawTokens();
        auto& tokens = m_lexer.getTokens();
        TokenType current;
        bool isExpression = false;
        std::stack<TokenType> brackets;
        for (auto& token : tokens)
        { 
            if (isExpression)
            {
                m_list.emplace_back(TokenType::Expression, "");
            }
            current = token.first;
            if (!operateBracketStack(brackets, current))
            {
                m_lexer.setError(ErrorCode::MissingLeftParenthesis, token.second);
                break;
            }

            if (token.first == TokenType::Keyword)
                current = GetKeyword(tokenList[token.second]);
            else if (token.first == TokenType::BinOperator)
                current = GetBinOperator(tokenList[token.second]);
            else if (token.first == TokenType::LogicalOperator)
                current = GetLogicalOperator(tokenList[token.second]);
            else if (token.first == TokenType::UniOperator)
                current = GetUniOperator(tokenList[token.second]);
   
            m_list.emplace_back(current,m_lexer.moveAt(token.second));
        }
        if (!brackets.empty())
        {
            m_lexer.setError(ErrorCode::NotClosedBracket, 0);
        }
    }
}
