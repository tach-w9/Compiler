#include <iostream>
#include "../token/token.h"
#include <cmath>
#include <cctype>
#include "parser.h"
#include "../lexer/lexer.cpp"

using namespace std;
template <typename T>
void addVector(vector<T>& vec1, vector<T>& vec2){
    
}
class Parser
{
private:
    vector<Token> tokens;
    int position = 0;

public:
    Parser(std::vector<Token> &tokens) : tokens(tokens) {}
    Token peek()
    {
        return tokens[position];
    }
    bool isAtEnd()
    {
        return (tokens[position].type == TokenTypes::END_OF_FILE);
    }
    void advance()
    {
        if (!isAtEnd())
            position++;
    }
    bool check(TokenTypes type)
    {
        if (peek().type == type)
            return 1;
        return 0;
    }
    bool isExpression(TokenTypes type)
    {
        switch (type)
        {
        case TokenTypes::INT_LIT:
        case TokenTypes::FLOAT_LIT:
        case TokenTypes::STRING_LIT:
        case TokenTypes::CHAR_LIT:
        case TokenTypes::BOOL_LIT:
        case TokenTypes::DOUBLE_LIT:
        case TokenTypes::IDENTIFIER:
        case TokenTypes::RIGHT_PAREN:
        case TokenTypes::LEFT_PAREN:
            return 1;
        }
        if (isOperator(type))
            return 1;
        return 0;
    }
    bool isPrimary(TokenTypes type)
    {
        switch (type)
        {
        case TokenTypes::INT_LIT:
        case TokenTypes::FLOAT_LIT:
        case TokenTypes::STRING_LIT:
        case TokenTypes::CHAR_LIT:
        case TokenTypes::BOOL_LIT:
        case TokenTypes::DOUBLE_LIT:
        case TokenTypes::IDENTIFIER:
            return 1;
        }
        return 0;
    }
    bool isNumber(TokenTypes type)
    {
        switch (type)
        {
        case TokenTypes::DOUBLE_LIT:
        case TokenTypes::INT_LIT:
        case TokenTypes::FLOAT_LIT:
            return 1;
        }
        return 0;
    }
    bool isString(TokenTypes type)
    {
        return (type == TokenTypes::STRING_LIT);
    }
    bool isChar(TokenTypes type)
    {
        return (type == TokenTypes::CHAR_LIT);
    }
    bool isIdentifier(TokenTypes type)
    {
        return (type == TokenTypes::IDENTIFIER);
    }
    bool isOperator(TokenTypes type)
    {
        for (const auto &[key, value] : operators)
        {
            if (type == value)
                return 1;
        }
        for (const auto &[key, value] : double_operators)
        {
            if (value == type)
                return 1;
        }
        return 0;
    }
    bool isMathOperator(TokenTypes type)
    {
        switch (type)
        {
        case TokenTypes::PLUS:
        case TokenTypes::MINUS:
        case TokenTypes::POWER:
        case TokenTypes::DIVIDE:
        case TokenTypes::MULTIPLY:
            return 1;
        }
        return 0;
    }
    bool isType(TokenTypes type)
    {
        switch (type)
        {
        case TokenTypes::TYPE_BOOL:
        case TokenTypes::TYPE_CHAR:
        case TokenTypes::TYPE_FLOAT:
        case TokenTypes::TYPE_DOUBLE:
        case TokenTypes::TYPE_INT:
        case TokenTypes::TYPE_STRING:
            return 1;
        }
        return 0;
    }
    Token parsePrimary()
    {
        if (isPrimary(peek().type))
        {
            Token token = peek();
            advance();
            return token;
        }
        return Token(TokenTypes::NULL_VAL, peek().column, peek().line, "");
    }
    bool isFactor(TokenTypes type)
    {
        switch (type)
        {
        case TokenTypes::POWER:
        case TokenTypes::MULTIPLY:
        case TokenTypes::DIVIDE:
            return 1;
        }
        return 0;
    }

    vector<Token> parseFactor()
    {
        vector<Token> varTokens;
        varTokens.push_back(parsePrimary());
        while (isFactor(peek().type))
        {
            varTokens.push_back(peek());
            advance();
            varTokens.push_back(parsePrimary());
        }
        return varTokens;
    }
    bool isTerm(TokenTypes type)
    {
        switch (type)
        {
        case TokenTypes::PLUS:
        case TokenTypes::MINUS:
            return 1;
        }
        return 0;
    }
    vector<Token> parseTerm(){
        vector<Token> varTokens;
        varTokens+=parseFactor();
        while(isTerm(peek().type)){
            varTokens.push_back(peek());
            advance();
            varTokens.push_back(parsePrimary());
        }
        return varTokens;
    }
    vector<Token> parseExpression()
    {
        vector<Token> varTokens;
        varTokens.push_back(parsePrimary());
        while (isMathOperator(peek().type))
        {
            varTokens.push_back(peek());
            advance();
            varTokens.push_back(parsePrimary());
        }
        return varTokens;
    }
};
int main()
{
    string source = "10 + 20 - 5;";
    Lexer lexer(source);
    vector<Token> tokens = lexer.tokenize();
    Parser parser(tokens);
    vector<Token> varTokens = parser.parseTerm();
    if (varTokens.size() == 0)
        cout << "Shiiit";
    for (const auto &token : varTokens)
    {
        cout << endl
             << tokenTypeToString(token.type);
    }
    return 0;
}
