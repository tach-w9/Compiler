#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <cmath>
using namespace std;

#define MAX_FLOAT pow(10, 38)
#define MIN_FLOAT pow(10, -38)
#define MAX_DOUBLE pow(10, 308)
#define MIN_DOUBLE pow(10, -308)
#define MAX_INT 2147483648
#define MIN_INT -2147483648
#define MAX_FLOAT_LENGTH 7
#define MAX_DOUBLE_LENGTH 15
#define MAX_INT_LENGTH 10

enum class TokenTypes
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_BOOL,
    INT_LIT,
    STRING_LIT,
    DOUBLE_LIT,
    FLOAT_LIT,
    CHAR_LIT,
    BOOL_LIT,
    IDENTIFIER,
    PLUS,
    MINUS,
    MULTIPLY,
    POWER,
    DIVIDE,
    EQUAL,
    EQUAL_EQUAL,
    BIGGER_THAN,
    BIGGER_THAN_OR_EQUAL,
    SMALLER_THAN,
    SMALLER_THAN_OR_EQUAL,
    NOT,
    NOT_EQUAL,
    SEMICOLON,
    AND,
    OR,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_BRACE,
    RIGHT_BRACE,
    DOUBLE_POINTS,
    POINT,
    COMMA,
    ARROW_LEFT,
    ARROW_RIGHT,
    IF,
    ELSE,
    ELSE_IF,
    SWITCH,
    CASE,
    CLASS,
    ENUM,
    FUNCTION,
    STRUCT,
    UNKNOWN,
    NEW_LINE,
    SPACE,
    TAB,
    NULL_VAL,
    WHILE,
    FOR,
    RETURN,
    SINGLE_AND,
    SINGLE_OR,
    BREAK,
    INVALID,
    END_OF_FILE
};
struct Token
{
    TokenTypes type;
    string value;
    int column;
    int line;
    string error = "";
    string expection = "";
    vector<string> errors;
    vector<string> expections;
    Token(TokenTypes t, int c, int l, string v) : value(v), type(t), column(c), line(l) {}
};
string tokenTypeToString(TokenTypes type)
{
    switch (type)
    {
    case TokenTypes::TYPE_INT:
        return "TYPE_INT";
    case TokenTypes::TYPE_FLOAT:
        return "TYPE_FLOAT";
    case TokenTypes::TYPE_STRING:
        return "TYPE_STRING";
    case TokenTypes::TYPE_DOUBLE:
        return "TYPE_DOUBLE";
    case TokenTypes::TYPE_CHAR:
        return "TYPE_CHAR";
    case TokenTypes::TYPE_BOOL:
        return "TYPE_BOOL";

    case TokenTypes::INT_LIT:
        return "INT_LIT";
    case TokenTypes::STRING_LIT:
        return "STRING_LIT";
    case TokenTypes::DOUBLE_LIT:
        return "DOUBLE_LIT";
    case TokenTypes::FLOAT_LIT:
        return "FLOAT_LIT";
    case TokenTypes::CHAR_LIT:
        return "CHAR_LIT";
    case TokenTypes::BOOL_LIT:
        return "BOOL_LIT";

    case TokenTypes::IDENTIFIER:
        return "IDENTIFIER";

    case TokenTypes::PLUS:
        return "PLUS";
    case TokenTypes::MINUS:
        return "MINUS";
    case TokenTypes::MULTIPLY:
        return "MULTIPLY";
    case TokenTypes::POWER:
        return "POWER";
    case TokenTypes::DIVIDE:
        return "DIVIDE";

    case TokenTypes::EQUAL:
        return "EQUAL";
    case TokenTypes::EQUAL_EQUAL:
        return "EQUAL_EQUAL";

    case TokenTypes::BIGGER_THAN:
        return "BIGGER_THAN";
    case TokenTypes::BIGGER_THAN_OR_EQUAL:
        return "BIGGER_THAN_OR_EQUAL";

    case TokenTypes::SMALLER_THAN:
        return "SMALLER_THAN";
    case TokenTypes::SMALLER_THAN_OR_EQUAL:
        return "SMALLER_THAN_OR_EQUAL";

    case TokenTypes::NOT:
        return "NOT";
    case TokenTypes::NOT_EQUAL:
        return "NOT_EQUAL";

    case TokenTypes::SEMICOLON:
        return "SEMICOLON";

    case TokenTypes::AND:
        return "AND";
    case TokenTypes::OR:
        return "OR";

    case TokenTypes::LEFT_PAREN:
        return "LEFT_PAREN";
    case TokenTypes::RIGHT_PAREN:
        return "RIGHT_PAREN";

    case TokenTypes::LEFT_BRACKET:
        return "LEFT_BRACKET";
    case TokenTypes::RIGHT_BRACKET:
        return "RIGHT_BRACKET";

    case TokenTypes::LEFT_BRACE:
        return "LEFT_BRACE";
    case TokenTypes::RIGHT_BRACE:
        return "RIGHT_BRACE";

    case TokenTypes::DOUBLE_POINTS:
        return "DOUBLE_POINTS";
    case TokenTypes::POINT:
        return "POINT";
    case TokenTypes::COMMA:
        return "COMMA";

    case TokenTypes::ARROW_LEFT:
        return "ARROW_LEFT";
    case TokenTypes::ARROW_RIGHT:
        return "ARROW_RIGHT";

    case TokenTypes::IF:
        return "IF";
    case TokenTypes::ELSE:
        return "ELSE";
    case TokenTypes::ELSE_IF:
        return "ELSE_IF";

    case TokenTypes::SWITCH:
        return "SWITCH";
    case TokenTypes::CASE:
        return "CASE";

    case TokenTypes::CLASS:
        return "CLASS";
    case TokenTypes::ENUM:
        return "ENUM";
    case TokenTypes::FUNCTION:
        return "FUNCTION";
    case TokenTypes::STRUCT:
        return "STRUCT";

    case TokenTypes::UNKNOWN:
        return "UNKNOWN";
    case TokenTypes::NEW_LINE:
        return "NEW_LINE";
    case TokenTypes::SPACE:
        return "SPACE";
    case TokenTypes::TAB:
        return "TAB";
    case TokenTypes::NULL_VAL:
        return "NULL_VAL";

    case TokenTypes::WHILE:
        return "WHILE";
    case TokenTypes::FOR:
        return "FOR";
    case TokenTypes::RETURN:
        return "RETURN";

    case TokenTypes::SINGLE_AND:
        return "SINGLE_AND";
    case TokenTypes::SINGLE_OR:
        return "SINGLE_OR";

    case TokenTypes::BREAK:
        return "BREAK";

    case TokenTypes::END_OF_FILE:
        return "END_OF_FILE";
    case TokenTypes::INVALID:
        return "INVALID";
    }

    return "UNKNOWN";
}
vector<char> alphabet = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '_', '$'};
vector<char> numbers_vec = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
std::unordered_map<std::string, TokenTypes> keywords = {
    {"int", TokenTypes::TYPE_INT},
    {"float", TokenTypes::TYPE_FLOAT},
    {"string", TokenTypes::TYPE_STRING},
    {"double", TokenTypes::TYPE_DOUBLE},
    {"char", TokenTypes::TYPE_CHAR},
    {"bool", TokenTypes::TYPE_BOOL},

    {"if", TokenTypes::IF},
    {"else", TokenTypes::ELSE},
    {"else_if", TokenTypes::ELSE_IF},
    {"switch", TokenTypes::SWITCH},
    {"case", TokenTypes::CASE},

    {"class", TokenTypes::CLASS},
    {"enum", TokenTypes::ENUM},
    {"function", TokenTypes::FUNCTION},
    {"struct", TokenTypes::STRUCT},

    {"while", TokenTypes::WHILE},
    {"for", TokenTypes::FOR},
    {"return", TokenTypes::RETURN},
    {"break", TokenTypes::BREAK},
    {"true", TokenTypes::BOOL_LIT},
    {"false", TokenTypes::BOOL_LIT}};

std::unordered_map<char, TokenTypes> operators = {
    {'+', TokenTypes::PLUS},
    {'-', TokenTypes::MINUS},
    {'*', TokenTypes::MULTIPLY},
    {'/', TokenTypes::DIVIDE},
    {'=', TokenTypes::EQUAL},

    {'>', TokenTypes::BIGGER_THAN},
    {'<', TokenTypes::SMALLER_THAN},
    {'!', TokenTypes::NOT},

    {';', TokenTypes::SEMICOLON},
    {',', TokenTypes::COMMA},
    {'.', TokenTypes::POINT},
    {':', TokenTypes::DOUBLE_POINTS},

    {'(', TokenTypes::LEFT_PAREN},
    {')', TokenTypes::RIGHT_PAREN},
    {'[', TokenTypes::LEFT_BRACKET},
    {']', TokenTypes::RIGHT_BRACKET},
    {'{', TokenTypes::LEFT_BRACE},
    {'}', TokenTypes::RIGHT_BRACE},

    {'&', TokenTypes::SINGLE_AND},
    {'|', TokenTypes::SINGLE_OR}};

std::unordered_map<std::string, TokenTypes> double_operators = {
    {"==", TokenTypes::EQUAL_EQUAL},
    {">=", TokenTypes::BIGGER_THAN_OR_EQUAL},
    {"<=", TokenTypes::SMALLER_THAN_OR_EQUAL},
    {"!=", TokenTypes::NOT_EQUAL},

    {"&&", TokenTypes::AND},
    {"||", TokenTypes::OR},

    {"->", TokenTypes::ARROW_RIGHT},
    {"<-", TokenTypes::ARROW_LEFT},

    {"**", TokenTypes::POWER}};

class Lexer
{
private:
    string src;
    int position = 0;
    int column = 0;
    int line = 0;

public:
    Lexer(const string &src) : src(src) {}
    char current()
    {
        return src[position];
    }
    bool isAtEnd()
    {
        return (position >= src.length());
    }
    void advance()
    {
        if (!isAtEnd())
        {
            if (current() == '\n')
            {
                column = 0;
                line++;
            }
            else
            {
                column++;
            }
            position++;
        }
    }
    void skipWhiteSpace()
    {
        while (!isAtEnd())
        {
            char c = current();
            if (c == ' ' || c == '\t' || c == '\n')
            {
                advance();
            }
            else
            {
                break;
            }
        }
    }
    bool isDigit()
    {
        if (isAtEnd())
            return 0;
        if (isdigit(current()))
            return 1;
        if (current() == '-' && position + 1 <= src.length() - 1 && isdigit(src[position + 1]))
            return 1;

        return 0;
    }
    bool isIdentifierStart()
    {
        if (isAtEnd())
            return 0;
        char c = current();
        for (int i = 0; i < alphabet.size(); i++)
        {

            if (c == alphabet[i])
            {
                if (c == 'R' && position + 1 <= src.length() - 1 && src[position + 1] == '"')
                {
                    return 0;
                }
                return 1;
            }
        }
        return 0;
    }
    bool isIdentifierPart()
    {
        if (isAtEnd())
            return 0;
        char c = current();
        for (int i = 0; i < alphabet.size(); i++)
        {

            if (c == alphabet[i])
                return 1;
        }
        for (int i = 0; i < numbers_vec.size(); i++)
        {
            if (c == numbers_vec[i])
                return 1;
        }
        return 0;
    }
    int HowMany(string text, char target)
    {
        int number = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] == target)
            {
                number++;
            }
        }
        return number;
    }
    Token scanIdentifier()
    {
        string ident = "";
        int start_column = column;
        if (isIdentifierStart())
        {
            ident += current();
            advance();
            while (isIdentifierPart())
            {
                ident += current();
                advance();
            }
        }
        if (ident != "")
        {
            for (const auto &[word, key] : keywords)
            {
                if (ident == word)
                {
                    Token token(key, start_column, (*this).line, ident);
                    return token;
                }
            }
            Token token(TokenTypes::IDENTIFIER, start_column, (*this).line, ident);
            return token;
        }
        Token token(TokenTypes::NULL_VAL, start_column, (*this).line, ident);
        return token;
    }
    Token scanNumber()
    {
        string value = "";
        int start_column = column;

        while (isDigit() || current() == '.')
        {
            value += current();
            advance();
        }
        if (!isAtEnd() && current() == '.')
        {
            value += '.';
            advance();
            while (isDigit())
            {
                value += current();
                advance();
            }
        }
        if (value != "")
        {
            TokenTypes type = TokenTypes::INT_LIT;
            string expection, error;
            int howmany = HowMany(value, '.');
            if (howmany > 0 && howmany <= 1)
            {
                // Floats can just resist for 7 decimal values
                if (value.length() - howmany <= MAX_FLOAT_LENGTH && stof(value) > MIN_FLOAT && stof(value) < MAX_FLOAT)
                {
                    type = TokenTypes::FLOAT_LIT;
                    if (value[value.length() - 1] == '.')
                        value += '0';
                    else if (value[0] == '.')
                        value.insert(0, "0");
                    else if (value.length() > 2 && value[0] == '-' && value[1] == '.')
                        value.insert(1, "0");
                }
                // DOUBLES can just resist for 15 decimal values
                else if (value.length() - howmany <= MAX_DOUBLE_LENGTH && stod(value) > MIN_DOUBLE && stod(value) < MAX_DOUBLE)
                {
                    type = TokenTypes::DOUBLE_LIT;
                    if (value[value.length() - 1] == '.')
                        value += '0';
                    else if (value[0] == '.')
                        value.insert(0, "0");
                    else if (value.length() > 2 && value[0] == '-' && value[1] == '.')
                        value.insert(1, "0");
                }
                else if (value.length() - howmany > MAX_DOUBLE_LENGTH)
                {
                    type = TokenTypes::INVALID;
                    error = "Out of range!";
                }
            }
            else if (howmany == 0)
            {
                int digitLength = value.length() - (value[0] == '-' ? 1 : 0);
                if (digitLength > MAX_INT_LENGTH || (stoi(value) < MIN_INT || stoi(value) > MAX_INT))
                {
                    type = TokenTypes::INVALID;
                    error = "Out of range!";
                }
                else
                {
                    type = TokenTypes::INT_LIT;
                    if (value.front() == '.')
                        value += '0';
                    else if (value[0] == '.')
                        value.insert(0, "0");
                    else if (value.length() > 2 && value[0] == '-' && value[1] == '.')
                        value.insert(1, "0");
                }
            }
            else
            {
                type = TokenTypes::INVALID;
                error = "Invalid floating point.";
            }
            Token token(type, start_column, (*this).line, value);
            token.error = error;
            token.expection = expection;
            return token;
        }
        Token token(TokenTypes::NULL_VAL, start_column, (*this).line, value);
        return token;
    }
    bool isOperator()
    {
        if (isAtEnd())
            return 0;
        char op = current();

        for (const auto &[oper, key] : operators)
        {
            if (op == oper)
            {
                return 1;
            }
        }
        if (!(position + 1 >= src.length()))
        {
            char double_op[2] = {op, src[position + 1]};
            for (const auto &[oper, key] : double_operators)
            {
                if (double_op[0] == oper[0] && double_op[1] == oper[1])
                {
                    return 1;
                }
            }
        }

        return 0;
    }

    Token scanOperator()
    {
        int start_column = column;
        string op = "";
        if (position + 1 < src.length())
        {
            string two = string(1, current()) + src[position + 1];
            if (double_operators.count(two))
            {
                op = two;
                advance();
                advance();
            }
        }
        if (op.empty())
        {
            op += current();
            advance();
        }
        for (const auto &[oper, key] : operators)
        {
            if (op.length() == 1 && op[0] == oper)
            {
                Token token(key, start_column, (*this).line, op);
                return token;
            }
        }
        for (const auto &[oper, key] : double_operators)
        {
            if (op == oper)
            {
                Token token(key, start_column, (*this).line, op);
                return token;
            }
        }
        Token token(TokenTypes::NULL_VAL, start_column, (*this).line, op);
        return token;
    }
    bool isStringStart()
    {
        if (isAtEnd())
            return 0;

        if (current() == '"' && isStringMultiline('"'))
        {
            cout << "Current is '";
            if (position > 0)
            {
                int j = 0;

                for (int i = position - 1; i >= 0 && src[i] == '\\'; i--)
                {
                    j++;
                }

                if (j % 2 == 0)
                {
                    return 1;
                }
            }
        }
        if (isStringMultiline('"'))
            return 1;

        return 0;
    }
    bool isStringMultiline(char target)
    {
        if (isAtEnd())
            return 0;
        if (current() == 'R' && position + 1 <= src.length() - 1 && src[position + 1] == target)
        {
            cout << "R2 is here \n\n\n";
            return 1;
        }
        return 0;
    }
    Token scanString()
    {
        string str = "";
        int start_column = column;
        int start_line = line;

        bool rawString = false;

        if (!isAtEnd() &&
            current() == 'R' &&
            position + 1 < src.length() &&
            src[position + 1] == '"')
        {
            rawString = true;

            str += current();
            advance();

            str += current();
            advance();
        }
        else if (!isAtEnd() && current() == '"')
        {
            str += current();
            advance();
        }
        else
        {
            return Token(TokenTypes::UNKNOWN, start_column, start_line, "");
        }

        while (!isAtEnd())
        {
            if (!rawString && current() == '\\' && position + 1 < src.length())
            {
                str += current();
                advance();
                str += current();
                advance();
                continue;
            }
            if (!rawString && current() == '"')
            {
                str += current();
                advance();
                break;
            }

            if (rawString && current() == '"')
            {
                str += current();
                advance();
                break;
            }

            str += current();
            advance();
        }

        TokenTypes type = TokenTypes::STRING_LIT;
        string error = "";
        string expection = "";

        if (str.length() < 2 || str.back() != '"')
        {
            type = TokenTypes::INVALID;
            error = "Expected \" after string definition (\")";
            expection = "\"";
        }

        if (!rawString && HowMany(str, '\n') > 0)
        {
            type = TokenTypes::INVALID;
            error = "Invalid String MultiLine Implementation! try to use 'R' before the string initialization.";
        }

        Token token(type, start_column, start_line, str);
        token.error = error;
        token.expection = expection;

        return token;
    }
    bool isCharStart()
    {
        if (isAtEnd())
            return 0;
        if (current() == '\'')
        {
            if (position == 0)
                return 1;

            int j = 0;
            for (int i = position - 1; i >= 0 && src[i] == '\\'; i--)
                j++;

            if (j % 2 == 0)
                return 1;

            return 0;
        }
        return 0;
    }

    Token scanChar()
    {
        string str = "";
        int start_column = column;
        int start_line = line;

        if (!isCharStart())
        {
            return Token(TokenTypes::UNKNOWN, start_column, start_line, "");
        }

        str += current();
        advance();

        while (!isAtEnd())
        {
            if (current() == '\\' && position + 1 < src.length())
            {
                str += current();
                advance();
                str += current();
                advance();
                continue;
            }
            if (current() == '\'')
            {
                str += current();
                advance();
                break;
            }
            str += current();
            advance();
        }

        TokenTypes type = TokenTypes::CHAR_LIT;
        string error = "", expection = "";
        if (str.length() < 2 || str.back() != '\'')
        {
            type = TokenTypes::INVALID;
            error = "Expected ' after char definition (')";
            expection = "'";
        }
        else
        {
            string inner = str.substr(1, str.length() - 2);
            if (HowMany(inner, '\n') > 0)
            {
                type = TokenTypes::INVALID;
                error = "Invalid Multiline Implementation for char";
            }
            else if (inner.empty())
            {
                type = TokenTypes::INVALID;
                error = "Empty char literal";
            }
            else if (inner.length() == 2 && inner[0] == '\\')
            {
                // escape صحيح
            }
            else if (inner.length() > 1)
            {
                type = TokenTypes::INVALID;
                error = "Char out of range";
            }
        }

        Token token(type, start_column, start_line, str);
        token.error = error;
        token.expection = expection;
        return token;
    }
    Token scanToken()
    {
        skipWhiteSpace();

        if (isAtEnd())
        {
            return Token(
                TokenTypes::END_OF_FILE,
                column,
                line,
                "");
        }

        Token token(
            TokenTypes::UNKNOWN,
            column,
            line,
            string(1, current()));
        if (isDigit())
        {
            token = scanNumber();
        }
        else if (isIdentifierStart())
        {
            token = scanIdentifier();
        }
        else if (isOperator())
        {
            token = scanOperator();
        } // we used current()=='"' because of the isStringstart function is designed for loop usage and not real if is string start
        else if (current() == '"' ||
                 (current() == 'R' &&
                  position + 1 < src.length() &&
                  src[position + 1] == '"'))
        {
            token = scanString();
        }
        else if (current() == '\'')
        {
            token = scanChar();
        }
        else
        {
            advance();
        }
        if (token.type == TokenTypes::UNKNOWN)
            token.error = "Unknown Charachter";
        return token;
    }
    vector<Token> tokenize()
    {
        vector<Token> tokens;

        while (!isAtEnd())
        {
            Token token = scanToken();
            tokens.push_back(token);
        }

        tokens.push_back(
            Token(TokenTypes::END_OF_FILE, column, line, ""));

        return tokens;
    }
};
class Parser
{
private:
    int position = 0;
    vector<Token> tokens;

public:
    Parser(const vector<Token> &tokens) : tokens(tokens) {}

    Token current()
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
        if (current().type == type)
            return 1;
        return 0;
    }
    bool consume(TokenTypes type)
    {
        bool res = check(type);
        if (res)
            advance();
        return res;
    }
    static bool isType(TokenTypes type)
    {
        vector<TokenTypes> types = {TokenTypes::TYPE_BOOL, TokenTypes::TYPE_CHAR, TokenTypes::TYPE_DOUBLE, TokenTypes::TYPE_FLOAT, TokenTypes::TYPE_INT, TokenTypes::TYPE_STRING};
        for (int i = 0; i < types.size(); i++)
        {
            if (type == types[i])
                return 1;
        }
        return 0;
    }
    bool isLiteral(TokenTypes type){
        switch(type){
            case TokenTypes::STRING_LIT:
            case TokenTypes::CHAR_LIT:
            case TokenTypes::BOOL_LIT:
            case TokenTypes::FLOAT_LIT:
            case TokenTypes::DOUBLE_LIT:
            case TokenTypes::INT_LIT:
                return 1;
        }
        return 0;
    }
    void pushMistak(vector<string> &arr, string s)
    {
        arr.push_back(s);
    }
    void pushFrontMistake(Token &arr)
    {
        arr.errors.insert(arr.errors.begin(), arr.error);
        arr.expections.insert(arr.expections.begin(), arr.expection);
    }
    static bool isOperator(TokenTypes type)
    {
        for (const auto &[first, second] : operators)
        {
            if (second == type)
                return 1;
        }
        for (const auto &[first, second] : double_operators)
        {
            if (second == type)
                return 1;
        }
        return 0;
    }
    bool isIdentifier(TokenTypes type)
    {
        return (type == TokenTypes::IDENTIFIER);
    }
    template <typename T,typename U>
    int HowMany(const std::vector<T> &arr, U target) const
    {
        int j = 0;
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (target == arr[i].type)
            {
                j++;
            }
        }
        return j;
    }
    template<typename T>
int HowManyArr(const std::vector<T>& arr, bool (*funcPtr)(TokenTypes)){
        int t = 0;
        for(size_t i = 0;i<arr.size();i++){
            if(funcPtr(arr[i].type)) t++;
        }
        cout << t;
        return t;
    }

    TokenTypes getLitByType(TokenTypes type)
    {
        if (isType(type))
        {
            switch (type)
            {
            case TokenTypes::TYPE_BOOL:
                return TokenTypes::BOOL_LIT;
            case TokenTypes::TYPE_CHAR:
                return TokenTypes::CHAR_LIT;
            case TokenTypes::TYPE_DOUBLE:
                return TokenTypes::DOUBLE_LIT;
            case TokenTypes::TYPE_FLOAT:
                return TokenTypes::FLOAT_LIT;
            case TokenTypes::TYPE_INT:
                return TokenTypes::INT_LIT;
            case TokenTypes::TYPE_STRING:
                return TokenTypes::STRING_LIT;
            default:
                return TokenTypes::UNKNOWN;
            }
        }
        return type;
    }
    bool matchesDeclaredType(TokenTypes declared, TokenTypes literalType)
    {
        if (literalType == getLitByType(declared))
            return true;
        if (declared == TokenTypes::TYPE_DOUBLE &&
            (literalType == TokenTypes::DOUBLE_LIT || literalType == TokenTypes::FLOAT_LIT))
            return true;
        return false;
    }
    bool parseVariableDeclaration()
    {
        if (isType(current().type))
        {
            vector<Token> varTokens;
            vector<string> errors;
            vector<string> expections;
            int previous_pos = position;
            while (!isAtEnd() && current().type != TokenTypes::SEMICOLON)
            {
                varTokens.push_back(current());
                advance();
            }
            if (current().type != TokenTypes::SEMICOLON)
            {
                pushMistak(errors, "Expected SemiCologn ';' after variable definition!");
                pushMistak(expections, ";");
                pushFrontMistake(varTokens.front());
                return 0;
            }
            else
                varTokens.push_back(current());
            position = previous_pos;
            bool is_init=false;
            if (varTokens.size() >= 2 && varTokens[1].type != TokenTypes::IDENTIFIER)
            {
                pushMistak(errors, "Expected an identifier after variable definition!");
                pushMistak(expections, "IDENTFIER");
                pushFrontMistake(varTokens.back());
                return 0;
            }
            else if(varTokens[0].type==TokenTypes::IDENTIFIER&&isOperator(varTokens[1].type)&&(isIdentifier(varTokens[2].type)||isLiteral(varTokens[2].type))) is_init=true;
            if (varTokens.size() >= 3 &&varTokens[2].type != TokenTypes::EQUAL&&varTokens[2].type!=TokenTypes::SEMICOLON)
            {
                pushMistak(errors, "Expected equal '=' after identifier definition!");
                pushMistak(expections, "=");
                pushFrontMistake(varTokens.back());
                return 0;
            }
            if (varTokens[2].type == TokenTypes::EQUAL)
            {
                int pos = 3;
                bool expectOperand = true;
                bool exprValid = true;
                while (pos < varTokens.size() - 1)
                {
                    if (expectOperand)
                    {
                        if (matchesDeclaredType(varTokens[0].type, varTokens[pos].type) || isIdentifier(varTokens[pos].type))
                        {
                            pos++;
                            expectOperand = false;
                        }
                        else { exprValid = false; break; }
                    }
                    else
                    {
                        if (isOperator(varTokens[pos].type) && varTokens[pos].type != TokenTypes::EQUAL)
                        {
                            pos++;
                            expectOperand = true;
                        }
                        else { exprValid = false; break; }
                    }
                }
                if (!exprValid || expectOperand || pos != varTokens.size() - 1)
                    return 0;
            }
        }
        
    else if (current().type == TokenTypes::IDENTIFIER)
    {
        vector<Token> varTokens;
        vector<string> errors;
        vector<string> expections;
        int previous_pos = position;
        while (!isAtEnd() && current().type != TokenTypes::SEMICOLON)
        {
            varTokens.push_back(current());
            advance();
        }
        if (current().type != TokenTypes::SEMICOLON)
        {
            pushMistak(errors, "Expected SemiCologn ';' after assignment!");
            pushMistak(expections, ";");
            pushFrontMistake(varTokens.front());
            return 0;
        }
        else
            varTokens.push_back(current());
        position = previous_pos;

        if (varTokens.size() < 3 || varTokens[1].type != TokenTypes::EQUAL)
            return 0;

        if (!isLiteral(varTokens[2].type) && !isIdentifier(varTokens[2].type))
            return 0;

        int pos = 3;
        bool expectOperand = false;
        bool exprValid = true;
        while (pos < varTokens.size() - 1)
        {
            if (expectOperand)
            {
                if (isLiteral(varTokens[pos].type) || isIdentifier(varTokens[pos].type))
                {
                    pos++;
                    expectOperand = false;
                }
                else { exprValid = false; break; }
            }
            else
            {
                if (isOperator(varTokens[pos].type) && varTokens[pos].type != TokenTypes::EQUAL)
                {
                    pos++;
                    expectOperand = true;
                }
                else { exprValid = false; break; }
            }
        }
        if (!exprValid || expectOperand || pos != varTokens.size() - 1)
            return 0;
    }
    else
        return 0;
    return 1;

    }
};

int main()
{
    vector<string> sources = {
    "double z = 123.456;",
    "double z = 1.5;",
    "float y = 10.5;",
    "float y = 123456789.123;",
    "int x = 10;",
    "double z = a + b;",
    "double z = \"hello\";"
};
    for (const string &source : sources)
    {
        cout << "\n========================================\n";
        cout << "Source: " << source << '\n';

        Lexer lexer(source);
        vector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);

        bool result = parser.parseVariableDeclaration();

        cout << "Result: "
             << (result ? "VALID" : "INVALID")
             << '\n';
    }

    return 0;
}
