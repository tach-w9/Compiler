#include <iostream>

#include <cctype>
#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;

#define MAX_FLOAT pow(10, 38)
#define MIN_FLOAT pow(10, -38)
#define MAX_DOUBLE pow(10, 308)
#define MIN_DOUBLE pow(10, -308)
constexpr long long MAX_INT = 2147483648;
constexpr long long MIN_INT = -2147483648;
constexpr int MAX_FLOAT_LENGTH = 7;
constexpr int MAX_DOUBLE_LENGTH = 15;
constexpr int MAX_INT_LENGTH = 10;

enum class TokenTypes {
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
    VOID,
    POINTER,
    SEA,
    UNKNOWN,
    NEW_LINE,
    SPACE,
    TAB,
    NULL_VAL,

    WHILE,
    FOR,
    RETURN,
    LEFT_EQUAL,

    SINGLE_AND,
    SINGLE_OR,

    STATIC,
    VIRTUAL,
    PRIVATE,
    PUBLIC,

    INLCUDE,

    OVERRIDE,
    FRIEND,
    PLUS_EQUAL,
    MINUS_EQUAL,
    DIVIDE_EQUAL,
    MULTI_EQUAL,
    COMMENT,
    BREAK,
    CONTINUE,
    INVALID,
    DEFAULT,
    INCREMENT,
    DECREMENT,
    QUESTION_MARK,
    NEW,
    DELETE,
    DOUBLE_LEFT,
    DOUBLE_RIGHT,

    LEFT,
    END_OF_FILE
};

struct Token {
    TokenTypes type;
    std::string value;
    int column;
    int line;

    std::string error = "";
    std::string expection = "";

    std::vector<std::string> errors;
    std::vector<std::string> expections;

    Token(TokenTypes t, int c, int l, std::string v)
        : type(t), value(v), column(c), line(l) {
    }
};

string tokenTypeToString(TokenTypes type) {
    switch (type) {
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

        case TokenTypes::INVALID:
            return "INVALID";
        case TokenTypes::VOID:
            return "VOID";
        case TokenTypes::POINTER:
            return "POINTER";
        case TokenTypes::END_OF_FILE:
            return "END_OF_FILE";
        case TokenTypes::PLUS_EQUAL:
            return "PLUS_EQUAL";

        case TokenTypes::MINUS_EQUAL:
            return "MINUS_EQUAL";
        case TokenTypes::CONTINUE:
            return "CONTINUE";
        case TokenTypes::MULTI_EQUAL:
            return "MULTIPLY_EQUAL";

        case TokenTypes::DIVIDE_EQUAL:
            return "DIVIDE_EQUAL";
        case TokenTypes::SEA:
            return "TLIDE";
        case TokenTypes::DEFAULT:
            return "DEFAULT";
        case TokenTypes::OVERRIDE:
            return "OVERRIDE";
        case TokenTypes::STATIC:
            return "STATIC";
        case TokenTypes::VIRTUAL:
            return "VIRTUAL";
        case TokenTypes::FRIEND:
            return "FRIEND";
        case TokenTypes::PUBLIC:
            return "PUBLIC";
        case TokenTypes::PRIVATE:
            return "PRIVATE";
        case TokenTypes::COMMENT:
            return "COMMENT";
        case TokenTypes::INCREMENT:
            return "INCREMENT";
        case TokenTypes::DECREMENT:
            return "DECREMENT";
        case TokenTypes::LEFT_EQUAL:
            return "LEFT_EQUAL";
        case TokenTypes::QUESTION_MARK:
            return "QUESTION_MARK";
        case TokenTypes::LEFT:
            return "LEFT";
        case TokenTypes::DELETE:
            return "DELETE";
        case TokenTypes::NEW:
            return "NEW";
        case TokenTypes::DOUBLE_LEFT:
            return "DOUBLE_LEFT";
        case TokenTypes::DOUBLE_RIGHT:
            return "DOUBLE_RIGHT";
    }

    return "UNKNOWN";
}

vector<char> alphabet =
{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

    '_',
    '$'
};

vector<char> numbers_vec =
{
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9'
};

std::unordered_map<std::string, TokenTypes> keywords =
{

    {"int", TokenTypes::TYPE_INT},
    {"float", TokenTypes::TYPE_FLOAT},
    {"string", TokenTypes::TYPE_STRING},
    {"double", TokenTypes::TYPE_DOUBLE},
    {"char", TokenTypes::TYPE_CHAR},
    {"bool", TokenTypes::TYPE_BOOL},
    {"void", TokenTypes::VOID},
    {"if", TokenTypes::IF},
    {"else", TokenTypes::ELSE},

    {"switch", TokenTypes::SWITCH},
    {"case", TokenTypes::CASE},

    {"class", TokenTypes::CLASS},
    {"enum", TokenTypes::ENUM},
    {"function", TokenTypes::FUNCTION},
    {"struct", TokenTypes::STRUCT},
    {"static", TokenTypes::STATIC},
    {"virtual", TokenTypes::VIRTUAL},
    {"private", TokenTypes::PRIVATE},
    {"public", TokenTypes::PUBLIC},

    {"while", TokenTypes::WHILE},
    {"for", TokenTypes::FOR},

    {"return", TokenTypes::RETURN},
    {"break", TokenTypes::BREAK},
    {"true", TokenTypes::BOOL_LIT},
    {"false", TokenTypes::BOOL_LIT},
    {"null", TokenTypes::NULL_VAL},
    {"include", TokenTypes::INLCUDE},
    {"pointer", TokenTypes::POINTER},
    {"continue", TokenTypes::CONTINUE},
    {"friend", TokenTypes::FRIEND},
    {"static", TokenTypes::STATIC},
    {"override", TokenTypes::OVERRIDE},
    {"virtual", TokenTypes::VIRTUAL},
    {"default", TokenTypes::DEFAULT},
    {"delete", TokenTypes::DELETE},
    {"new",TokenTypes::NEW},
    {"enum",TokenTypes::ENUM},
};

std::unordered_map<char, TokenTypes> operators =
{
    {'+', TokenTypes::PLUS},
    {'-', TokenTypes::MINUS},
    {'*', TokenTypes::MULTIPLY},
    {'/', TokenTypes::DIVIDE},
    {'=', TokenTypes::EQUAL},
    {'%', TokenTypes::LEFT},
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
    {'|', TokenTypes::SINGLE_OR},
    {'~', TokenTypes::SEA},
    {'?', TokenTypes::QUESTION_MARK},
    {'\n', TokenTypes::NEW_LINE},
    {' ', TokenTypes::SPACE},
    {'\t', TokenTypes::TAB}
};

std::unordered_map<std::string, TokenTypes> double_operators =
{
    {"==", TokenTypes::EQUAL_EQUAL},
    {">=", TokenTypes::BIGGER_THAN_OR_EQUAL},
    {"<=", TokenTypes::SMALLER_THAN_OR_EQUAL},
    {"!=", TokenTypes::NOT_EQUAL},
    {"&&", TokenTypes::AND},
    {"||", TokenTypes::OR},
    {"->", TokenTypes::ARROW_RIGHT},
    {"<-", TokenTypes::ARROW_LEFT},
    {"**", TokenTypes::POWER},
    {"+=", TokenTypes::PLUS_EQUAL},
    {"-=", TokenTypes::MINUS_EQUAL},
    {"*=", TokenTypes::MULTI_EQUAL},
    {"/=", TokenTypes::DIVIDE_EQUAL},
    {"%=", TokenTypes::LEFT_EQUAL},
    {"++", TokenTypes::INCREMENT},
    {"--", TokenTypes::DECREMENT},
    {"<<",TokenTypes::DOUBLE_LEFT},
    {">>",TokenTypes::DOUBLE_RIGHT},
};

class Lexer {
private:
    string src;
    int position = 0;
    int column = 0;
    int line = 0;

public:
    Lexer(const string &src) : src(src) {
    }

    char current() {
        return src[position];
    }

    bool isAtEnd() {
        return (position >= src.length());
    }

    void advance() {
        if (!isAtEnd()) {
            if (current() == '\n') {
                column = 0;
                line++;
            } else {
                column++;
            }
            position++;
        }
    }

    void skipWhiteSpace() {
        while (!isAtEnd()) {
            char c = current();
            if (c == ' ' || c == '\t' || c == '\n') {
                advance();
            } else {
                break;
            }
        }
    }

    bool isDigit() {
        if (isAtEnd())
            return 0;
        return isdigit(current());
    }

    bool isIdentifierStart() {
        if (isAtEnd())
            return 0;
        char c = current();
        for (int i = 0; i < alphabet.size(); i++) {
            if (c == alphabet[i]) {
                if (c == 'R' && position + 1 <= src.length() - 1 && src[position + 1] == '"') {
                    return 0;
                }
                return 1;
            }
        }
        return 0;
    }

    bool isIdentifierPart() {
        if (isAtEnd())
            return 0;
        char c = current();
        for (int i = 0; i < alphabet.size(); i++) {
            if (c == alphabet[i])
                return 1;
        }
        for (int i = 0; i < numbers_vec.size(); i++) {
            if (c == numbers_vec[i])
                return 1;
        }
        return 0;
    }

    int HowMany(string text, char target) {
        int number = 0;
        for (int i = 0; i < text.length(); i++) {
            if (text[i] == target) {
                number++;
            }
        }
        return number;
    }

    bool isComment() {
        return (!isAtEnd() && position + 1 < src.length() && current() == '/' && src[position + 1] == '/');
    }

    bool isMultiLineCommentStart() {
        return (!isAtEnd() && position + 1 < src.length() && current() == '/' && src[position + 1] == '*');
    }

    Token scanComment() {
        if (isComment()) {
            string value;
            int start_column = column;
            value += current();
            advance();
            value += current();
            advance();
            while (!isAtEnd() && current() != '\n') {
                value += current();

                advance();
            }
            return Token(TokenTypes::COMMENT, start_column, (*this).line, value);
        } else if (isMultiLineCommentStart()) {
            string value;
            int start_column = column;
            value += current();
            advance();
            value += current();
            advance();
            while (!isAtEnd() && current() != '*' && src[position + 1] != '\\') {
                value += current();
                advance();
            }
            return Token(TokenTypes::COMMENT, start_column, (*this).line, value);
        }
        return Token(TokenTypes::COMMENT, (*this).column, (*this).line, "");
    }

    Token scanIdentifier() {
        string ident = "";
        int start_column = column;
        if (isIdentifierStart()) {
            ident += current();
            advance();
            while (isIdentifierPart()) {
                ident += current();
                advance();
            }
        }
        if (ident != "") {
            for (const auto &[word, key]: keywords) {
                if (ident == word) {
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

    Token scanNumber() {
        string value = "";
        int start_column = column;

        while (isDigit() || current() == '.') {
            value += current();
            advance();
        }
        if (!isAtEnd() && current() == '.') {
            value += '.';
            advance();
            while (isDigit()) {
                value += current();
                advance();
            }
        }
        if (value != "") {
            TokenTypes type = TokenTypes::INT_LIT;
            string expection, error;
            int howmany = HowMany(value, '.');
            if (howmany > 0 && howmany <= 1) {
                // Floats can just resist for 7 decimal values
                if (value.length() - howmany <= MAX_FLOAT_LENGTH && stof(value) > MIN_FLOAT && stof(value) <
                    MAX_FLOAT) {
                    type = TokenTypes::FLOAT_LIT;
                    if (value[value.length() - 1] == '.')
                        value += '0';
                    else if (value[0] == '.')
                        value.insert(0, "0");
                    else if (value.length() > 2 && value[0] == '-' && value[1] == '.')
                        value.insert(1, "0");
                } else if (value.length() - howmany <= MAX_DOUBLE_LENGTH && stod(value) > MIN_DOUBLE && stod(value) <
                           MAX_DOUBLE) {
                    type = TokenTypes::DOUBLE_LIT;
                    if (value[value.length() - 1] == '.')
                        value += '0';
                    else if (value[0] == '.')
                        value.insert(0, "0");
                    else if (value.length() > 2 && value[0] == '-' && value[1] == '.')
                        value.insert(1, "0");
                } else if (value.length() - howmany > MAX_DOUBLE_LENGTH) {
                    type = TokenTypes::INVALID;
                    error = "Out of range!";
                }
            } else if (howmany == 0) {
                int digitLength = value.length() - (value[0] == '-' ? 1 : 0);
                if (digitLength > MAX_INT_LENGTH || (stoi(value) < MIN_INT || stoi(value) > MAX_INT)) {
                    type = TokenTypes::INVALID;
                    error = "Out of range!";
                } else {
                    type = TokenTypes::INT_LIT;
                    if (value.front() == '.')
                        value += '0';
                    else if (value[0] == '.')
                        value.insert(0, "0");
                    else if (value.length() > 2 && value[0] == '-' && value[1] == '.')
                        value.insert(1, "0");
                }
            } else {
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

    bool isOperator() {
        if (isAtEnd())
            return 0;
        char op = current();

        for (const auto &[oper, key]: operators) {
            if (op == oper) {
                return 1;
            }
        }
        if (!(position + 1 >= src.length())) {
            char double_op[2] = {op, src[position + 1]};
            for (const auto &[oper, key]: double_operators) {
                if (double_op[0] == oper[0] && double_op[1] == oper[1]) {
                    return 1;
                }
            }
        }

        return 0;
    }

    Token scanOperator() {
        int start_column = column;
        string op = "";
        if (position + 1 < src.length()) {
            string two = string(1, current()) + src[position + 1];
            if (double_operators.count(two)) {
                op = two;
                advance();
                advance();
            }
        }
        if (op.empty()) {
            op += current();
            advance();
        }
        for (const auto &[oper, key]: operators) {
            if (op.length() == 1 && op[0] == oper) {
                Token token(key, start_column, (*this).line, op);
                return token;
            }
        }
        for (const auto &[oper, key]: double_operators) {
            if (op == oper) {
                Token token(key, start_column, (*this).line, op);
                return token;
            }
        }
        Token token(TokenTypes::NULL_VAL, start_column, (*this).line, op);
        return token;
    }

    bool isStringStart() {
        if (isAtEnd())
            return 0;

        if (current() == '"' && isStringMultiline('"')) {
            cout << "Current is '";
            if (position > 0) {
                int j = 0;

                for (int i = position - 1; i >= 0 && src[i] == '\\'; i--) {
                    j++;
                }

                if (j % 2 == 0) {
                    return 1;
                }
            }
        }
        if (isStringMultiline('"'))
            return 1;

        return 0;
    }

    bool isStringMultiline(char target) {
        if (isAtEnd())
            return 0;
        if (current() == 'R' && position + 1 <= src.length() - 1 && src[position + 1] == target) {
            cout << "R2 is here \n\n\n";
            return 1;
        }
        return 0;
    }

    Token scanString() {
        string str = "";
        int start_column = column;
        int start_line = line;

        bool rawString = false;

        if (!isAtEnd() &&
            current() == 'R' &&
            position + 1 < src.length() &&
            src[position + 1] == '"') {
            rawString = true;

            str += current();
            advance();

            str += current();
            advance();
        } else if (!isAtEnd() && current() == '"') {
            str += current();
            advance();
        } else {
            return Token(TokenTypes::UNKNOWN, start_column, start_line, "");
        }

        while (!isAtEnd()) {
            if (!rawString && current() == '\\' && position + 1 < src.length()) {
                str += current();
                advance();
                str += current();
                advance();
                continue;
            }
            if (!rawString && current() == '"') {
                str += current();
                advance();
                break;
            }

            if (rawString && current() == '"') {
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

        if (str.length() < 2 || str.back() != '"') {
            type = TokenTypes::INVALID;
            error = "Expected \" after string definition (\")";
            expection = "\"";
        }

        if (!rawString && HowMany(str, '\n') > 0) {
            type = TokenTypes::INVALID;
            error = "Invalid String MultiLine Implementation! try to use 'R' before the string initialization.";
        }

        Token token(type, start_column, start_line, str);
        token.error = error;
        token.expection = expection;

        return token;
    }

    bool isCharStart() {
        if (isAtEnd())
            return 0;
        if (current() == '\'') {
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

    Token scanChar() {
        string str = "";
        int start_column = column;
        int start_line = line;

        if (!isCharStart()) {
            return Token(TokenTypes::UNKNOWN, start_column, start_line, "");
        }

        str += current();
        advance();

        while (!isAtEnd()) {
            if (current() == '\\' && position + 1 < src.length()) {
                str += current();
                advance();
                str += current();
                advance();
                continue;
            }
            if (current() == '\'') {
                str += current();
                advance();
                break;
            }
            str += current();
            advance();
        }

        TokenTypes type = TokenTypes::CHAR_LIT;
        string error = "", expection = "";
        if (str.length() < 2 || str.back() != '\'') {
            type = TokenTypes::INVALID;
            error = "Expected ' after char definition (')";
            expection = "'";
        } else {
            string inner = str.substr(1, str.length() - 2);
            if (HowMany(inner, '\n') > 0) {
                type = TokenTypes::INVALID;
                error = "Invalid Multiline Implementation for char";
            } else if (inner.empty()) {
                type = TokenTypes::INVALID;
                error = "Empty char literal";
            } else if (inner.length() == 2 && inner[0] == '\\') {
                // escape صحيح
            } else if (inner.length() > 1) {
                type = TokenTypes::INVALID;
                error = "Char out of range";
            }
        }

        Token token(type, start_column, start_line, str);
        token.error = error;
        token.expection = expection;
        return token;
    }

    Token scanToken() {
        skipWhiteSpace();

        if (isAtEnd()) {
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
        if (isComment() || isMultiLineCommentStart()) {
            token = scanComment();
        } else if (isDigit()) {
            token = scanNumber();
        } else if (isIdentifierStart()) {
            token = scanIdentifier();
        } else if (isOperator()) {
            token = scanOperator();
        } // we used current()=='"' because of the isStringstart function is designed for loop usage and not real if is string start
        else if (current() == '"' ||
                 (current() == 'R' &&
                  position + 1 < src.length() &&
                  src[position + 1] == '"')) {
            token = scanString();
        } else if (current() == '\'') {
            token = scanChar();
        } else {
            advance();
        }
        if (token.type == TokenTypes::UNKNOWN)
            token.error = "Unknown Charachter";
        return token;
    }

    vector<Token> tokenize() {
        vector<Token> tokens;

        while (!isAtEnd()) {
            Token token = scanToken();
            tokens.push_back(token);
        }

        return tokens;
    }
};

vector<string> TypeRelatedExpressions = {
    "sizeof",
};
class Node {
private:
    string name = "";
    int loop = 0;

public:
    virtual ~Node() = default;

    virtual void print(int indent) = 0;

    virtual string getName() {
        return (*this).name;
    }

    virtual void setName(const string n) {
        (*this).name = n;
    }

    virtual void setLoop(int i) {
        (*this).loop = i;
    }

    virtual int getLoop() {
        return (*this).loop;
    }

    friend string getName(Node *n);
};

string getName(Node *n) {
    return (*n).name;
}

class EmptyNode : public Node {
public:
    void print(int indent) override {
    }
};

class Position : public Node {
public:
    int isPrefix;
    int isPostfix;

    Position(int isPer = 0, int isPost = 0) : isPrefix(isPer), isPostfix(isPost) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "Position: " << ((isPrefix) ? "Prefix" : (isPostfix) ? "Postfix" : "Hoo Lee Shiit");
    }
};

class LiteralNode : public Node {
public:
    Token val;

    LiteralNode(Token value) : val(value) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "LiteralNode: " << val.value;
    }
};

class IdentifierNode : public Node {
public:
    Token val;

    IdentifierNode(Token value) : val(value) {
    }

    void print(int indent) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "IdentifierNode: " << val.value;
    }
};

class BinaryNode : public Node {
public:
    Node *left;
    Node *right;
    Token oper;

    BinaryNode(Token oper, Node *left, Node *right) : right(right), left(left), oper(oper) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "BinaryNode: " << oper.value;
        (*left).print(indent + 1);
        (*right).print(indent + 1);
    }
};

class UnaryNode : public Node {
public:
    Token op;
    Node *oper;
    int isPosition;
    Node *Position;

    UnaryNode(Node *oper, Token value, int isPosition = 0, Node *pos = new EmptyNode) : op(value), oper(oper),
        isPosition(isPosition), Position(pos) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "UnaryOperator: " << op.value;
        (*oper).print(indent + 1);
        if (isPosition) {
            (*Position).print(indent + 1);
        }
    }
};

class TernaryNode : public Node {
public:
    Node *Condition;
    Node *Then;
    Node *Else;

    TernaryNode(Node *cond, Node *Then, Node *Else) : Else(Else), Condition(cond), Then(Then) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "TernaryNode";
        (*Condition).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Then";
        (*Then).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Else";
        (*Else).print(indent + 2);
    }
};

class ExpressionStatment : public Node {
private:
    string name = "ExpressionStatment";

public:
    Node *Expression;

    ExpressionStatment(Node *exper) : Expression(exper) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ExpressionStatment";
        (*Expression).print(indent + 2);
    }
};

class VariableDeclarationNode : public Node {
private:
    string name = "VariableDeclarationNode";

public:
    Token type;
    Node *identifier;
    Node *Initializer;
    int isObject;
    int isProp;
    Node *Type;

    VariableDeclarationNode(Node *Init, Token type, Node *ident, int isobj = 0, int isProp = 0,
                            Node *t = nullptr) : Initializer(Init), identifier(ident), type(type), isObject(isobj),
                                                 isProp(isProp), Type(t) {
        setName("VariableDeclarationNode");
    }

    void construct(Node *conster) {
        if (dynamic_cast<EmptyNode *>(conster))
            return;
        Initializer = conster;
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "VariableDeclaration";

        if (!isProp) {
            cout << endl;
            for (int i = 0; i < indent + 1; i++) {
                cout << "  ";
            }
            cout << "Type: " << type.value;
        } else
            (*Type).print(indent + 1);

        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        (*identifier).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }

        cout << "Initializer";
        (*Initializer).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "isObject: " << ((isObject) ? "True" : "False");
    }
};

class Initializer : public Node {
public:
    Node *Expression;

    Initializer(Node *exper) : Expression(exper) {
    }

    void print(int indent = 0) override {
        (*Expression).print(indent);
    }
};


class IfStatment : public Node {
private:
    string name = "IfStatment";

public:
    Node *Condition;
    Node *ThenBlock;
    Node *Elseblock = new EmptyNode();
    vector<Node *> ElseIfBlocks;

    IfStatment(Node *cond, Node *block) : ThenBlock(block), Condition(cond) {
    }

    void addElseIfNode(Node *elseif) {
        ElseIfBlocks.push_back(elseif);
    }

    void addElseNode(Node *node) {
        Elseblock = node;
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "IfStatment";
        (*Condition).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "ThenBranch";
        (*ThenBlock).print(indent + 2);
        for (int i = 0; i < ElseIfBlocks.size(); i++) {
            (*ElseIfBlocks[i]).print(indent + 1);
        }
        (*Elseblock).print(indent + 1);
    }
};

class ElseIfStatment : public Node {
public:
    Node *Condition;
    Node *ThenBlock;

    ElseIfStatment(Node *cond, Node *block) : Condition(cond), ThenBlock(block) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ElseIfStatment";
        (*Condition).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "ThenBranch";
        (*ThenBlock).print(indent + 2);
    }
};

class ElseStatment : public Node {
public:
    Node *Block;

    ElseStatment(Node *b) : Block(b) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ElseStatment";
        (*Block).print(indent + 1);
    }
};

class WhileStatment : public Node {
public:
    Node *Condition;
    Node *Block;

    WhileStatment(Node *c, Node *b) : Condition(c), Block(b) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "WhileStatment";
        (*Condition).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Body";
        (*Block).print(indent + 2);
    }
};

class ReturnStatment : public Node {
public:
    Node *Expression;

    ReturnStatment(Node *e) : Expression(e) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ReturnStatment";
        (*Expression).print(indent + 1);
    }
};

class Condition : public Node {
public:
    Node *ConditionExpression;

    Condition(Node *CExper) : ConditionExpression(CExper) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "Condition";
        (*ConditionExpression).print(indent + 1);
    }
};

class Block : public Node {
public:
    vector<Node *> nodes;

    void print(int indent = 0) {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "Block";
        for (int i = 0; i < nodes.size(); i++) {
            (*nodes[i]).print(indent + 1);
        }
    }

    void addNode(Node *node) {
        (*this).nodes.push_back(node);
    }
};

class ForStatment : public Node {
public:
    Node *Initialisation;
    Node *Condition;
    Node *Increment;
    Node *Body;

    ForStatment(Node *i, Node *c, Node *in, Node *b) : Initialisation(i), Condition(c), Body(b), Increment(in) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ForStatment" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Initialisation";
        (*Initialisation).print(indent + 2);
        (*Condition).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Increment";
        (*Increment).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Body";
        (*Body).print(indent + 2);
    }
};

class BreakStatment : public Node {
public:
    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "BreakStatment";
    }
};

class ContinueStatment : public Node {
public:
    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ContinueStatment";
    }
};

class Parameter : public Node {
public:
    Node *VariableDecalarationNode;

    Parameter(Node *v) : VariableDecalarationNode(v) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "Parameter";
        (*VariableDecalarationNode).print(indent + 1);
    }
};

class FunctionStatment : public Node {
private:
    string name = "Function";

public:
    Token Type;
    Node *Name;
    vector<Node *> Parameters;
    Node *Body;
    Node *type;
    int isProp;

    FunctionStatment(Token t, Node *b, Node *n, int isProp = 0, Node *T = nullptr) : Type(t), Name(n), Body(b), type(T),
        isProp(isProp) {
    }

    void addParam(Node *p) {
        Parameters.push_back(p);
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "FunctionStatement";
        if (!isProp) {
            cout << endl;
            for (int i = 0; i < indent + 1; i++) {
                cout << "  ";
            }
            cout << "Type: " << Type.value << endl;
        } else {
            (*type).print(indent + 1);
            cout << endl;
        }
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Name";
        (*Name).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Parameters";
        for (int i = 0; i < Parameters.size(); i++) {
            (*Parameters[i]).print(indent + 2);
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Body";
        (*Body).print(indent + 2);
    }
};

class CallExpression : public Node {
public:
    Node *Callee;
    vector<Node *> Arguments;

    CallExpression(Node *cal) : Callee(cal) {
    }

    void addArg(Node *n) {
        Arguments.push_back(n);
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "CallExpression" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Callee";
        (*Callee).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Arguments";
        for (Node *n: Arguments) {
            (*n).print(indent + 2);
        }
    }
};

class ArrayDeclarationNode : public Node {
public:
    Token Type;
    Node *Name;
    vector<Node *> Sizes;
    Node *Initializer;

    ArrayDeclarationNode(Token t, Node *n, Node *i = new EmptyNode()) : Type(t), Name(n), Initializer(i) {
    }

    void addSize(Node *s) {
        Sizes.push_back(s);
    }

    void initialize(Node *init) {
        (*this).Initializer = init;
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ArrayDeclarationNode" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Type: " << Type.value;
        (*Name).print(indent + 1);
        for (int i = 0; i < Sizes.size(); i++) {
            cout << endl;
            for (int i = 0; i < indent + 1; i++) {
                cout << "  ";
            }
            cout << "Size" << i + 1;
            (*Sizes[i]).print(indent + 2);
        }

        (*Initializer).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Dimensions: " << Sizes.size();
    }
};

class ArrayInit : public Node {
public:
    vector<Node *> args;
    int isObject;

    ArrayInit(int isObject = 0) : isObject(isObject) {
    }

    void addArg(Node *arg) {
        args.push_back(arg);
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ArrayInitializerNode";
        for (Node *n: args) {
            (*n).print(indent + 1);
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "isObjectInitialisation: " << ((isObject) ? "True" : "False");
    }
};

class ArrayArg : public Node {
public:
    Node *Expression;

    ArrayArg(Node *exper) : Expression(exper) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ArrayArg";
        (*Expression).print(indent + 1);
    }
};

class ArrayAccessNode : public Node {
public:
    Node *Name;
    Node *Index;

    ArrayAccessNode(Node *n, Node *i) : Name(n), Index(i) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ArrayAccessNode" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Array";
        (*Name).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Index";
        (*Index).print(indent + 2);
    }
};

class FieldDeclaration : public Node {
public:
    Node *VariableDeclaration;

    FieldDeclaration(Node *v) : VariableDeclaration(v) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "FieldDeclaration";
        (*VariableDeclaration).print(indent + 1);
    }
};

class MemberInitializer : public Node {
private:
    string name = "Method";

public:
    Node *Member;
    Node *Value;

    MemberInitializer(Node *mem, Node *val) : Member(mem), Value(val) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "MemberInitializer" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Member";
        (*Member).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Value";
        (*Value).print(indent + 2);
    }
};

class ConstructorNode : public Node {
private:
    string name = "ConstructorNode";

public:
    Node *ObjectName;
    vector<Node *> Params;
    vector<Node *> Initilizators;
    Node *Body;

    ConstructorNode(Node *obj_n) : ObjectName(obj_n) {
        setName("Constructor");
    }

    void addParam(Node *shii) {
        Params.push_back(shii);
    }

    void addInit(Node *init) {
        Initilizators.push_back(init);
    }

    void body(Node *body) {
        (*this).Body = body;
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ConstructorNode";
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "ObjectName";
        (*ObjectName).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Parameters";
        for (Node *n: Params) {
            (*n).print(indent + 2);
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Initializators";
        for (Node *init: Initilizators) {
            (*init).print(indent + 2);
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Body";
        (*Body).print(indent + 2);
    }
};

class DestructorNode : public Node {
private:
    string name = "DestructorNode";

public:
    Node *Callee;
    Node *Body;
    int isDefault;
    int isVirtual;

    DestructorNode(Node *cal, int isAbs = 0, int isV = 0) : Callee(cal), isDefault(isAbs), isVirtual(isV) {
        setName("Destructor");
    }

    void body(Node *body) {
        (*this).Body = body;
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "DestructorNode";
        (*Callee).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "isDefault: " << ((isDefault) ? "True" : "False") << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "isVirtual: " << ((isVirtual) ? "True" : "False") << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Body";
        (*Body).print(indent + 2);
    }
};

class MethodStatment : public Node {
private:
    string name = "MethodStatmen";

public:
    Token Type;
    Node *Name;
    vector<Node *> Parameters;
    Node *Body;
    int isFriend;
    int isOverride;
    int isStatic;
    int isVirtual;

    MethodStatment(Token t, Node *b, Node *n, int f = 0, int o = 0, int s = 0, int v = 0) : Type(t), Name(n), Body(b),
        isFriend(f), isOverride(o), isStatic(s), isVirtual(v) {
        setName("MethodStatment");
    }

    void addParam(Node *p) {
        Parameters.push_back(p);
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "Method" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Type: " << Type.value << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Name";
        (*Name).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Parameters";
        for (int i = 0; i < Parameters.size(); i++) {
            (*Parameters[i]).print(indent + 2);
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Body";
        (*Body).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "isVirtual: " << ((isVirtual) ? "True" : "False") << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "isOverride: " << ((isOverride) ? "True" : "False") << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "isStatic: " << ((isStatic) ? "True" : "False") << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "isFriend: " << ((isFriend) ? "True" : "False");
    }
};

class PublicNode : public Node {
private:
    string name = "PublicNode";

public:
    PublicNode() {
        setName("PublicNode");
    }

    void print(int indent = 0) override {
    }
};

class PrivateNode : public Node {
private:
    string name = "PrivateNode";

public:
    PrivateNode() {
        setName("PrivateNode");
    }

    void print(int indent = 0) override {
    }
};

class StructDeclaration : public Node {
public:
    Node *Name;
    Node *Constructor = new EmptyNode();
    Node *Destructor = new EmptyNode();
    vector<Node *> PrivateFields;
    vector<Node *> PublicFields;
    vector<Node *> Methods;
    Node *Body = new EmptyNode();

    StructDeclaration(Node *n) : Name(n) {
    }

    void addPrivateField(Node *field) {
        PrivateFields.push_back(field);
    }

    void addPublicField(Node *field) {
        PublicFields.push_back(field);
    }

    void addMethod(Node *method) {
        Methods.push_back(method);
    }

    void body(Node *body) {
        (*this).Body = body;
    }

    void constructor(Node *conster) {
        (*this).Constructor = conster;
    }

    void destructor(Node *dester) {
        (*this).Destructor = dester;
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "StructDeclaration" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Name";
        (*Name).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "PrivateFields";
        for (Node *n: PrivateFields) {
            (*n).print(indent + 2);
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "PublicFields";
        for (Node *n: PublicFields) {
            (*n).print(indent + 2);
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Methods";
        for (Node *Method: Methods) {
            (*Method).print(indent + 2);
        }
        (*Constructor).print(indent + 1);
        (*Destructor).print(indent + 1);
    }
};

class ClassDeclaration : public Node {
public:
    Node *Name;
    Node *Constructor = new EmptyNode();
    Node *Destructor = new EmptyNode();
    vector<Node *> PrivateFields;
    vector<Node *> PublicFields;
    vector<Node *> Methods;

    ClassDeclaration(Node *Name) : Name(Name) {
    }

    void constructor(Node *conster) {
        (*this).Constructor = conster;
    }

    void destructor(Node *dester) {
        (*this).Destructor = dester;
    }

    void addPrivateField(Node *Field) {
        (*this).PrivateFields.push_back(Field);
    }

    void addPublicField(Node *Field) {
        (*this).PublicFields.push_back(Field);
    }

    void addMethod(Node *Field) {
        (*this).Methods.push_back(Field);
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ClassDeclaration" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "PrivateFields";
        for (Node *n: PrivateFields) {
            (*n).print(indent + 2);
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "PublicFields";
        for (Node *n: PublicFields) {
            (*n).print(indent + 2);
        }
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Methods";
        for (Node *n: Methods) {
            (*n).print(indent + 2);
        }
        (*Constructor).print(indent + 1);
        (*Destructor).print(indent + 1);
    }
};

class PointerType : public Node {
public:
    Node *Type;
    Token type;
    int isManPtr;

    PointerType(Token T, const int M = 0, Node *t = new EmptyNode()) : Type(t), type(T), isManPtr(M) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "PointerType";
        if (!isManPtr) {
            cout << endl;
            for (int i = 0; i < indent + 2; i++) {
                cout << "  ";
            }

            cout << "BaseType: " << type.value;
        } else
            (*Type).print(indent + 2);
    }
};

class RefereceType : public Node {
public:
    Token Type;

    RefereceType(Token t) : Type(t) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "ReferenceType" << endl;
        for (int i = 0; i < indent + 2; i++) {
            cout << "  ";
        }
        cout << "BaseType: " << Type.value;
    }
};

class MemberAccessNode : public Node {
public:
    Node *Object;
    Node *Member;

    MemberAccessNode(Node *obj = new EmptyNode, Node *Member = new EmptyNode) : Object(obj), Member(Member) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "MemberAccessNode" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Object";
        (*Object).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Member";
        (*Member).print(indent + 2);
    }
};

class PointerAccessNode : public Node {
public:
    Node *Object;
    Node *Member;

    PointerAccessNode(Node *obj = new EmptyNode, Node *mem = new EmptyNode) : Object(obj), Member(mem) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "PointerAccessNode" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Object";
        (*Object).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Member";
        (*Member).print(indent + 2);
    }
};

class DereferenceNode : public Node {
public:
    Node *Expression;

    DereferenceNode(Node *exper) : Expression(exper) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "DereferenceNode";
        (*Expression).print(indent + 1);
    }
};

class AddressNode : public Node {
public:
    Node *Identifier;

    AddressNode(Node *ident) : Identifier(ident) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "AddressNode";
        (*Identifier).print(indent + 1);
    }
};

class TryNode : public Node {
public:
    Node *Block;
    vector<Node *> Catches;

    TryNode(Node *block) : Block(block) {
    }

    void addCatch(Node *cat) {
        Catches.push_back(cat);
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "TryNode" << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Body";
        (*Block).print(indent + 2);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Catches";
        for (Node *n: Catches) {
            (*n).print(indent + 2);
        }
    }
};

class CatchNode : public Node {
public:
    Node *Exception;
    Node *Block;
    int isElse;

    CatchNode(Node *Except, Node *Block, int iselse = 0) : isElse(iselse), Block(Block), Exception(Except) {
    }

    void print(int indent = 0) {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "CatchNode" << endl;
        (*Exception).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Body";
        (*Block).print(indent + 2);
    }
};

class CastNode : public Node {
public:
    Token Type;
    Node *Expression;
    int isProb;
    Node *type;

    CastNode(Token t, Node *exper, int isprob = 0, Node *T = new EmptyNode) : Type(t), Expression(exper),
                                                                              isProb(isprob), type(T) {
    }

    void print(int indent = 0) override {
        cout << endl;
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "CastNode";

        if (!isProb) {
            cout << endl;
            for (int i = 0; i < indent + 1; i++) {
                cout << "  ";
            }
            cout << "Type: " << Type.value;
        } else
            (*type).print(indent + 1);
        cout << endl;
        for (int i = 0; i < indent + 1; i++) {
            cout << "  ";
        }
        cout << "Expression";
        (*Expression).print(indent + 2);
    }
};
class NewNode: public Node {
public:
    Token type;
    vector<Node*> Args;
    NewNode(Token t):type(t){}
    void addArg(Node* arg) {
        Args.push_back(arg);
    }
    void print(int indent = 0)override {
        cout << endl;
        for (int i = 0;i<indent;i++) {
            cout << "  ";
        }
        cout << "NewNode" << endl;
        for (int i = 0;i<indent+1;i++) {
            cout << "  ";
        }
        cout << "Type: " << type.value << endl;
        for (int i = 0;i<indent+1;i++) {
            cout << "  ";
        }
        cout << "Arguments";
        for (Node* n:Args) {
            (*n).print(indent+2);
        }

    }
};

class DeleteExpression: public Node {
public:
    Node* Expression;
    DeleteExpression(Node* exper):Expression(exper){}
    void print(int indent = 0)override {
        cout << endl;
        for (int i = 0;i<indent;i++) {
            cout << "  ";
        }
        cout << "DeleteExpression";
        (*Expression).print(indent+1);
    }
};
class TypeRelatedNode: public Node {
public:
    Token Type;
    int isProp;
    Node* type;
    TypeRelatedNode(Token type,int isprop=0,Node* Type = new EmptyNode):Type(type),isProp(isprop),type(Type){}
};
class ExpressionRelatedNode: public Node {
public:
    Node* Expression;
    ExpressionRelatedNode(Node* exper):Expression(exper){}

};
class SizeOfTypeNode: public TypeRelatedNode {
public:
    void print(int indent = 0)override {
        cout << endl;
        for (int i = 0;i<indent;i++) {
            cout << "  ";
        }
        cout << "SizeOfTypeNode";
        if (!isProp) {
            cout << endl;
            for (int i = 0;i<indent+1;i++) {
                cout << "  ";
            }
            cout << "Type: " << Type.value;
        }else
            (*type).print(indent+1);

    }


    SizeOfTypeNode(Token type, int is_prop, Node * node):TypeRelatedNode(type,is_prop,node){}
};
class SizeOfExpressionnode: public ExpressionRelatedNode {
public:
    void print(int indent = 0)override {
        cout << endl;
        for (int i = 0;i<indent;i++) {
            cout << "  ";
        }
        cout << "SizeOfExpressionNode";
        (*Expression).print(indent+1);
    }
    SizeOfExpressionnode(Node * node):ExpressionRelatedNode(node){}
};
class Program : public Node {
public:
    vector<Node *> nodes;

    void addNode(Node *node) {
        (*this).nodes.push_back(node);
    }

    void print(int indent = 0) {
        cout << endl
                << "Program";
        for (int i = 0; i < nodes.size(); i++) {
            (*nodes[i]).print(indent + 1);
        }
    }

    ~Program() {
        for (auto ptr: nodes) {
            delete ptr;
        }
        nodes.clear();
    }
};

class Parser {
public:
    vector<Token> tokens;
    int position = 0;
    vector<string> objects;

    Parser(vector<Token> tokens) : tokens(tokens) {
        skipCommentes();
    }

    void addObject(string thing) {
        objects.push_back(thing);
    }

    void skipCommentes() {
        vector<Token> cleaned;
        for (auto &t: tokens)
            if (t.type != TokenTypes::COMMENT)
                cleaned.push_back(t);
        tokens = cleaned;
    }

    Token peek() {
        return tokens[position];
    }

    int isAtEnd() {
        return (peek().type == TokenTypes::END_OF_FILE);
    }

    void advance() {
        if (!isAtEnd())
            position++;
    }

    int check(TokenTypes type) {
        if (peek().type == type)
            return 1;
        return 0;
    }

    int except(TokenTypes type) {
        if (check(type)) {
            advance();
            return 1;
        }
        throw std::runtime_error(
            "Type is not the same! For Type:  " + tokenTypeToString(type) + "to Type: " + tokenTypeToString(peek().type)
            + " value: " + peek().value
            + "Line: " + to_string(peek().line) + "Col: " + to_string(peek().column));
        return 0;
    }

    int isValue(TokenTypes type) {
        switch (type) {
            case TokenTypes::INT_LIT:
            case TokenTypes::FLOAT_LIT:
            case TokenTypes::DOUBLE_LIT:
            case TokenTypes::STRING_LIT:
            case TokenTypes::CHAR_LIT:
            case TokenTypes::BOOL_LIT:
            case TokenTypes::IDENTIFIER:
                return 1;
        }
        return 0;
    }

    int isNumber(TokenTypes type) {
        switch (type) {
            case TokenTypes::DOUBLE_LIT:
            case TokenTypes::INT_LIT:
            case TokenTypes::FLOAT_LIT:
                return 1;
        }
        return 0;
    }

    int isChar(TokenTypes type) {
        return (type == TokenTypes::CHAR_LIT);
    }

    int isString(TokenTypes type) {
        return (type == TokenTypes::STRING_LIT);
    }

    int isBool(TokenTypes type) {
        return (type == TokenTypes::BOOL_LIT);
    }

    int isOperator(TokenTypes type) {
        for (const auto &[key, value]: operators) {
            if (value == type)
                return 1;
        }
        for (const auto &[key, value]: double_operators) {
            if (value == type)
                return 1;
        }
        return 0;
    }

    int isFactor(TokenTypes type) {
        switch (type) {
            case TokenTypes::DIVIDE:
            case TokenTypes::MULTIPLY:
            case TokenTypes::POWER:
            case TokenTypes::LEFT:
                return 1;
        }
        return 0;
    }

    int isTerm(TokenTypes type) {
        return (type == TokenTypes::PLUS || type == TokenTypes::MINUS);
    }

    int isIdentifier(TokenTypes type) {
        return (type == TokenTypes::IDENTIFIER);
    }

    int isType(TokenTypes type) {
        switch (type) {
            case TokenTypes::TYPE_BOOL:
            case TokenTypes::TYPE_CHAR:
            case TokenTypes::TYPE_DOUBLE:
            case TokenTypes::TYPE_FLOAT:
            case TokenTypes::TYPE_INT:
            case TokenTypes::TYPE_STRING:
            case TokenTypes::VOID:
                return 1;
        }
        return 0;
    }

    int isObject(int isCustom=0,string value="") {
        string target = ((isCustom)?value:peek().value);
        for (const string name: objects) {
            if (target == name)
                return 1;
        }
        return 0;
    }

    int isComparison(TokenTypes type) {
        switch (type) {
            case TokenTypes::BIGGER_THAN:
            case TokenTypes::SMALLER_THAN:
            case TokenTypes::EQUAL_EQUAL:
            case TokenTypes::SMALLER_THAN_OR_EQUAL:
            case TokenTypes::BIGGER_THAN_OR_EQUAL:
            case TokenTypes::NOT_EQUAL:
                return 1;
        }
        return 0;
    }

    int checkElseIf() {
        if (check(TokenTypes::ELSE_IF))
            return 1;
        if (check(TokenTypes::ELSE) && position + 1 < (int) tokens.size() && tokens[position + 1].type ==
            TokenTypes::IF)
            return 1;
        return 0;
    }

    bool isLogicalAnd(TokenTypes type) {
        return (type == TokenTypes::AND);
    }

    bool isLogicalOr(TokenTypes type) {
        return (type == TokenTypes::OR);
    }

    int isIncrement(TokenTypes type) {
        return (type == TokenTypes::INCREMENT);
    }

    int isDecrement(TokenTypes type) {
        return (type == TokenTypes::DECREMENT);
    }
    int isTypeRelatedExpression(Token token) {
        for (const string& n:TypeRelatedExpressions) {
            if (token.value==n)
                return 1;
        }
        return 0;
    }
    bool isUnary(TokenTypes type) {
        switch (type) {
            case TokenTypes::PLUS:
            case TokenTypes::MINUS:
            case TokenTypes::NOT:
                return 1;
        }
        return 0;
    }

    bool isParen(TokenTypes type) {
        return (type == TokenTypes::LEFT_PAREN || type == TokenTypes::RIGHT_PAREN);
    }

    bool isBrace(Node *stmt) {
        return !(dynamic_cast<IfStatment *>(stmt) || dynamic_cast<WhileStatment *>(stmt) || dynamic_cast<ElseStatment *>
                 (stmt) || dynamic_cast<ElseIfStatment *>(stmt) || dynamic_cast<ForStatment *>(stmt) || dynamic_cast<
                     FunctionStatment *>(stmt));
    }

    Node *parseCast() {
        advance();
        Token type = peek();
        advance();
        int isProp = 0;
        Node *Type = new EmptyNode();
        if (check(TokenTypes::MULTIPLY)) {
            Type = new PointerType(type);
            isProp = 1;
            advance();
        } else if (check(TokenTypes::POWER)) {
            int ptrs = 2;
            advance();
            while (check(TokenTypes::POWER) || check(TokenTypes::MULTIPLY)) {
                if (check(TokenTypes::MULTIPLY))
                    ptrs++;
                else
                    ptrs += 2;
                advance();
            }
            Node *ptr = new PointerType(type);
            for (int i = 0; i < ptrs - 1; i++) {
                ptr = new PointerType(type, 1, ptr);
            }
            Type = ptr;
            isProp = 1;
        }
        except(TokenTypes::RIGHT_PAREN);
        Node *expr = parseUnary();
        return new CastNode(type, expr, isProp, Type);

        return expr;
    }

    Node* parseDeleteExpression() {
        advance();
        Node* exper = parseExpression();
        return new DeleteExpression(exper);
    }
    Node *parsePrimary() {
        if (isTypeRelatedExpression(peek()))
            return parseTypeRelatedExpressions();
        if (check(TokenTypes::NEW)&&position+1<tokens.size()&&tokens[position+1].type==TokenTypes::IDENTIFIER)
            return parseNewNode();
        if (check(TokenTypes::DELETE))
            return parseDeleteExpression();
        if (check(TokenTypes::LEFT_PAREN) &&
    position + 1 < tokens.size() &&
    isType(tokens[position+1].type)||
    isObject(1,tokens[position+1].value)) {
            int lookahead = position + 2;
            while (lookahead < tokens.size() &&
                  (tokens[lookahead].type == TokenTypes::MULTIPLY ||
                   tokens[lookahead].type == TokenTypes::POWER))
                lookahead++;
            return parseCast();
    }
        if (isObject() && position + 1 < tokens.size() && tokens[position + 1].type == TokenTypes::LEFT_PAREN)
            return parseCalleeExpression(1, new IdentifierNode(peek()));
        if ((check(TokenTypes::MULTIPLY) || check(TokenTypes::SINGLE_AND)) && position + 1 < tokens.size() && (
                tokens[position + 1].type == TokenTypes::LEFT_PAREN || tokens[position + 1].type ==
                TokenTypes::IDENTIFIER)) {
            if (check(TokenTypes::MULTIPLY))
                return parseDereferenceNode();
            else
                return parseAddressOfNode();
        }
        if (isValue(peek().type)) {
            Token token = peek();
            advance();
            if (isIdentifier(token.type))
                return new IdentifierNode(token);
            return new LiteralNode(token);
        } else if (peek().type == TokenTypes::LEFT_PAREN) {
            advance();
            Node *expression = parseExpression();
            if (peek().type == TokenTypes::RIGHT_PAREN)
                advance();
            return expression;
        }
        throw std::runtime_error(
            "Unexpected token: " + peek().value + " (" + tokenTypeToString(peek().type) + ") at line " + to_string(
                peek().line));
    }

    Node *parseUnary() {
        if (isUnary(peek().type)) {
            Token op = peek();
            advance();

            Node *operand = parseUnary();

            return new UnaryNode(operand, op);
        }
        if (check(TokenTypes::INCREMENT) || check(TokenTypes::DECREMENT) && position + 1 < tokens.size() && tokens[
                position + 1].type == TokenTypes::IDENTIFIER) {
            Token op = peek();
            advance();
            Node *operand = parseUnary();
            return new UnaryNode(operand, op, 1, new Position(1, 0));
        }

        Node *node = parsePrimary();

        while (true) {
            if (check(TokenTypes::POINT)) {
                advance();

                Token member = peek();
                except(TokenTypes::IDENTIFIER);

                node = new MemberAccessNode(
                    node,
                    new IdentifierNode(member)
                );

                continue;
            }
            if (check(TokenTypes::ARROW_RIGHT)) {
                advance();

                Token member = peek();
                except(TokenTypes::IDENTIFIER);

                node = new PointerAccessNode(
                    node,
                    new IdentifierNode(member)
                );

                continue;
            }
            if (check(TokenTypes::INCREMENT) || check(TokenTypes::DECREMENT)) {
                Token op = peek();
                advance();
                node = new UnaryNode(node, op, 1, new Position(0, 1));
                continue;
            }
            if (check(TokenTypes::LEFT_PAREN)) {
                node = parseCalleeExpression(node);
                continue;
            }
            if (check(TokenTypes::LEFT_BRACKET)) {
                advance();

                Node *index = parseExpression();

                except(TokenTypes::RIGHT_BRACKET);

                node = new ArrayAccessNode(
                    node,
                    index
                );

                continue;
            }
            if (check(TokenTypes::DELETE)) {
                advance();
                Node* exper = parseExpression();
                return new DeleteExpression(exper);
            }

            break;
        }

        return node;
    }

    Node *parseFactor() {
        Node *left = parseUnary();
        while (isFactor(peek().type)) {
            Token op = peek();
            advance();
            Node *right = parseUnary();
            left = new BinaryNode(op, left, right);
        }
        return left;
    }

    Node *parseTerm() {
        Node *left = parseFactor();
        while (isTerm(peek().type)) {
            Token op = peek();
            advance();
            Node *right = parseFactor();
            left = new BinaryNode(op, left, right);
        }
        return left;
    }

    Node *parseComparison() {
        Node *left = parseTerm();
        while (isComparison(peek().type)||peek().type==TokenTypes::DOUBLE_LEFT||peek().type==TokenTypes::DOUBLE_RIGHT) {
            Token op = peek();
            advance();
            Node *right = parseTerm();
            left = new BinaryNode(op, left, right);
        }
        return left;
    }

    Node *parseLogicalAnd() {
        Node *left = parseComparison();
        while (isLogicalAnd(peek().type)) {
            Token op = peek();
            advance();
            Node *right = parseComparison();
            left = new BinaryNode(op, left, right);
        }
        return left;
    }

    Node *parseLogicalOr() {
        Node *left = parseLogicalAnd();
        while (isLogicalOr(peek().type)||peek().type==TokenTypes::SINGLE_OR) {
            Token op = peek();
            advance();
            Node *right = parseLogicalAnd();
            left = new BinaryNode(op, left, right);
        }
        return left;
    }

    Node *parseTernary() {
        Node *cond = parseLogicalOr();
        if (check(TokenTypes::QUESTION_MARK)) {
            advance();
            Node *then = parseTernary();
            except(TokenTypes::DOUBLE_POINTS);
            Node *els = parseTernary();
            return new TernaryNode(cond, then, els);
        }
        return cond;
    }
    Node *parseAssignment() {
        Node *left = parseTernary();
        if (peek().type == TokenTypes::EQUAL ||
            peek().type == TokenTypes::PLUS_EQUAL ||
            peek().type == TokenTypes::MINUS_EQUAL ||
            peek().type == TokenTypes::MULTI_EQUAL ||
            peek().type == TokenTypes::DIVIDE_EQUAL ||
            peek().type == TokenTypes::LEFT_EQUAL) {
            Token op = peek();
            advance();
            Node *right = parseAssignment();
            left = new BinaryNode(op, left, right);
        }
        return left;
    }

    Node *parseExpression() {
        return parseAssignment();
    }

    Node *parseExpressionStatment() {
        return new ExpressionStatment(parseExpression());
    }

    Node *parseArrayAssignment(int isObject = 0, int isObjectInit = 0) {
        ArrayInit *arr = new ArrayInit(isObjectInit);
        while (!check(TokenTypes::RIGHT_BRACE)) {
            if (check(TokenTypes::LEFT_BRACE) && !isObject) {
                advance();
                (*arr).addArg(parseArrayAssignment());
            } else
                (*arr).addArg(new ArrayArg(parseExpression()));
            if (check(TokenTypes::COMMA))
                advance();
        }
        except(TokenTypes::RIGHT_BRACE);
        return arr;
    }

    Node *parseVariableDeclaration(int isObject = 0) {
        if (isObject &&
            position + 1 < tokens.size() &&
            tokens[position + 1].type == TokenTypes::LEFT_PAREN) {
            Node *Callee = new IdentifierNode(peek());

            return parseCalleeExpression(
                1,
                Callee
            );
        }
        Token type = peek();
        advance();
        int isProp = 0;
        Node *Type = new EmptyNode();
        if (check(TokenTypes::SINGLE_AND)) {
            Type = new RefereceType(type);
            isProp = 1;
            advance();
        } else if (check(TokenTypes::MULTIPLY)) {
            Type = new PointerType(type);
            isProp = 1;
            advance();
        } else if (check(TokenTypes::POWER)) {
            int ptrs = 2;
            advance();
            while (check(TokenTypes::POWER) || check(TokenTypes::MULTIPLY)) {
                if (check(TokenTypes::MULTIPLY))
                    ptrs++;
                else
                    ptrs += 2;
                advance();
            }
            Node *ptr = new PointerType(type);
            for (int i = 0; i < ptrs - 1; i++) {
                ptr = new PointerType(type, 1, ptr);
            }
            Type = ptr;
            isProp = 1;
        }
        Node *construct = new EmptyNode();
        if (!isIdentifier(peek().type))
            throw std::runtime_error(
                "Expected identifier after type definition!, Type: " + tokenTypeToString(peek().type) + " value: " +
                peek().value + " Line: " + to_string(peek().line) + " Col: " + to_string(peek().column));

        Token ident = peek();
        Node *identifier = new IdentifierNode(ident);
        if (position + 1 < tokens.size() &&
            tokens[position + 1].type == TokenTypes::LEFT_PAREN)
            construct = parseCalleeExpression(1, new IdentifierNode(type));
        else
            advance();
        if (check(TokenTypes::LEFT_BRACKET)) {
            ArrayDeclarationNode *array_declaration_node = new ArrayDeclarationNode(type, identifier);
            Node *expression = new EmptyNode();
            while (peek().type == TokenTypes::LEFT_BRACKET) {
                advance();
                Node *Size = parseExpression();
                except(TokenTypes::RIGHT_BRACKET);
                (*array_declaration_node).addSize(Size);
            }
            if (check(TokenTypes::EQUAL)) {
                advance();
                if (except(TokenTypes::LEFT_BRACE)) {
                    expression = parseArrayAssignment(0, 1);
                }
            }
            (*array_declaration_node).initialize(new Initializer(expression));
            return array_declaration_node;
        }


        Node *expression = new EmptyNode();
        if (peek().type == TokenTypes::EQUAL) {
            advance();
            if (isObject && check(TokenTypes::LEFT_BRACE)) {
                advance();
                expression = parseArrayAssignment(1);
            } else
                expression = parseExpression();
        }
        Node *initializer = new Initializer(expression);
        VariableDeclarationNode *variable = new VariableDeclarationNode(initializer, type, identifier, isObject, isProp,
                                                                        Type);
        if (isObject)
            (*variable).construct(construct);
        return variable;
    }

    Node *parseCondition() {
        return parseExpression();
    }

    Node *parseBlock(int loop = 0) {
        Block *block = new Block();
        if (except(TokenTypes::LEFT_BRACE)) {
            while (peek().type != TokenTypes::RIGHT_BRACE) {
                Node *stmt = parseStatment(loop);
                (*stmt).setLoop(loop);
                (*block).addNode(stmt);
                if (peek().type == TokenTypes::SEMICOLON)
                    advance();
            }

            advance();
        }
        return block;
    }

    Node *parseIfStatment(int loop = 0) noexcept {
        advance();
        if (except(TokenTypes::LEFT_PAREN)) {
            Node *ConditionExpression = parseCondition();
            Node *condition = new Condition(ConditionExpression);
            if (except(TokenTypes::RIGHT_PAREN)) {
                Node *Block = parseBlock(loop);
                Node *ElseBlock = new EmptyNode();

                IfStatment *ifstmt = new IfStatment(condition, Block);

                while (checkElseIf()) {
                    if (check(TokenTypes::ELSE))
                        advance();
                    (*ifstmt).addElseIfNode(parseElseIfStatment(loop));
                }
                if (check(TokenTypes::ELSE)) {
                    ElseBlock = parseElseStatment(loop);
                }
                (*ifstmt).addElseNode(ElseBlock);
                return ifstmt;
            }
        }
        return new EmptyNode();
    }

    Node *parseElseIfStatment(int loop = 0) noexcept {
        advance();
        if (except(TokenTypes::LEFT_PAREN)) {
            Node *ConditionExpression = parseCondition();
            Node *condition = new Condition(ConditionExpression);
            if (except(TokenTypes::RIGHT_PAREN)) {
                Node *Block = parseBlock(loop);
                return new ElseIfStatment(condition, Block);
            }
        }
        return new EmptyNode();
    }

    Node *parseElseStatment(int loop = 0) {
        advance();
        Node *block = parseBlock(loop);
        return new ElseStatment(block);
    }

    Node *parseWhileStatment(int loop = 0) noexcept {
        advance();
        if (except(TokenTypes::LEFT_PAREN)) {
            Node *ConditionExpression = parseCondition();
            Node *condition = new Condition(ConditionExpression);
            if (except(TokenTypes::RIGHT_PAREN)) {
                Node *Block = parseBlock(loop);
                return new WhileStatment(condition, Block);
            }
        }
        return new EmptyNode();
    }

    Node *parseForStatment(int loop = 0) {
        advance();
        if (except(TokenTypes::LEFT_PAREN)) {
            Node *Initialisation = new EmptyNode();
            if (!check(TokenTypes::SEMICOLON)) {
                if (isType(peek().type))
                    Initialisation = parseVariableDeclaration();
                else
                    Initialisation = parseExpressionStatment();
            }

            except(TokenTypes::SEMICOLON);
            Node *condition = new EmptyNode();
            if (!check(TokenTypes::SEMICOLON)) {
                Node *ConditionExpression = parseCondition();
                condition = new Condition(ConditionExpression);
            }
            except(TokenTypes::SEMICOLON);
            Node *Incrementation = new EmptyNode();
            if (!check(TokenTypes::RIGHT_PAREN)) {
                Incrementation = parseExpression();
            }
            if (except(TokenTypes::RIGHT_PAREN)) {
                Node *Body = parseBlock(loop);
                return new ForStatment(Initialisation, condition, Incrementation, Body);
            }
        }
        return new EmptyNode();
    }

    Node *parseBreakStatment() {
        advance();
        Node *Break = new BreakStatment();
        (*Break).setName("break");
        return Break;
    }

    Node *parseContinueStatment() {
        advance();
        Node *Continue = new ContinueStatment();
        (*Continue).setName("continue");
        return Continue;
    }

    Node *parseReturnStatment() {
        advance();
        Node *Expression = parseExpression();
        Node *Return = new ReturnStatment(Expression);
        (*Return).setName("return");
        return Return;
    }

    vector<Node *> parseParameters() {
        advance();
        vector<Node *> params;
        while (!check(TokenTypes::RIGHT_PAREN)) {
            params.push_back(new Parameter(parseVariableDeclaration()));
            if (check(TokenTypes::COMMA))
                advance();
        }
        except(TokenTypes::RIGHT_PAREN);
        return params;
    }

    Node *parseFunction(int object = 0) {
        int isFriend = 0;
        int isOverride = 0;
        int isVirtual = 0;
        int isStatic = 0;
        while (check(TokenTypes::FRIEND) || check(TokenTypes::STATIC) || check(TokenTypes::VIRTUAL) || check(
                   TokenTypes::OVERRIDE)) {
            if (check(TokenTypes::FRIEND)) {
                isFriend = 1;
                advance();
            } else if (check(TokenTypes::STATIC)) {
                isStatic = 1;
                advance();
            } else if (check(TokenTypes::VIRTUAL)) {
                isVirtual = 1;
                advance();
            } else if (check(TokenTypes::OVERRIDE)) {
                isOverride = 1;
                advance();
            }
        }
        if (isFriend || isOverride || isVirtual || isStatic) {
            except(TokenTypes::FUNCTION);
        } else
            advance();
        Token name = peek();
        if (except(TokenTypes::IDENTIFIER)) {
            Node *Name = new IdentifierNode(name);

            if (check(TokenTypes::LEFT_PAREN)) {
                vector<Node *> params = parseParameters();
                Token Type = Token(TokenTypes::UNKNOWN, 0, 0, "");
                Type.value = "";
                if (isType(peek().type) || isObject()) {
                    Type = peek();
                    advance();
                }
                Node *type = new EmptyNode();
                int isProp = 0;
                if (check(TokenTypes::SINGLE_AND)) {
                    isProp = 1;
                    type = new RefereceType(Type);
                    advance();
                } else if (check(TokenTypes::MULTIPLY)) {
                    isProp = 1;
                    type = new PointerType(Type);
                    advance();
                }

                Node *Body = parseBlock();
                if (object) {
                    MethodStatment *method = new MethodStatment(Type, Body, Name, isFriend, isOverride, isStatic,
                                                                isVirtual);
                    for (int i = 0; i < params.size(); i++) {
                        (*method).addParam(params[i]);
                    }
                    return method;
                }
                FunctionStatment *fun = new FunctionStatment(Type, Body, Name, isProp, type);
                for (int i = 0; i < params.size(); i++) {
                    (*fun).addParam(params[i]);
                }
                return fun;
            } else {
                except(TokenTypes::LEFT_PAREN);
            }
        }
        return new EmptyNode();
    }

    Node *parseCalleeExpression(int isobject = 0, Node *callee = new EmptyNode()) {
        Node *Callee = new EmptyNode();
        if (isobject)
            Callee = callee;
        else
            Callee = new IdentifierNode(peek());
        advance();

        if (except(TokenTypes::LEFT_PAREN)) {
            vector<Node *> Args;

            while (!check(TokenTypes::RIGHT_PAREN)) {
                if (isType(peek().type) || (isObject() && position + 1 < tokens.size() && tokens[position + 1].type ==
                                            TokenTypes::IDENTIFIER))
                    Args.push_back(parseVariableDeclaration());
                else
                    Args.push_back(parseExpression());
                if (check(TokenTypes::COMMA))
                    advance();
            }
            except(TokenTypes::RIGHT_PAREN);
            if (check(TokenTypes::DOUBLE_POINTS)) {
                advance();
                ConstructorNode *Constructor = new ConstructorNode(Callee);
                for (Node *Arg: Args) {
                    (*Constructor).addParam(Arg);
                }
                while (!check(TokenTypes::LEFT_BRACE)) {
                    (*Constructor).addInit(parseMemberInitializer());
                    if (check(TokenTypes::COMMA))
                        advance();
                }
                Node *Body = parseBlock();
                (*Constructor).body(Body);
                return Constructor;
            }
            CallExpression *callee = new CallExpression(Callee);
            for (Node *arg: Args) {
                (*callee).addArg(arg);
            }
            return callee;
        }
        return new EmptyNode();
    }

    Node *parseCalleeExpression(Node *callee) {
        except(TokenTypes::LEFT_PAREN);

        vector<Node *> Args;

        while (!check(TokenTypes::RIGHT_PAREN)) {
            if (isType(peek().type))
                Args.push_back(parseVariableDeclaration());
            else
                Args.push_back(parseExpression());

            if (check(TokenTypes::COMMA))
                advance();
            else
                break;
        }

        except(TokenTypes::RIGHT_PAREN);

        CallExpression *call = new CallExpression(callee);

        for (Node *arg: Args)
            (*call).addArg(arg);

        return call;
    }

    Node *parseDestructor() {
        int isVirtual = 0;
        if (check(TokenTypes::VIRTUAL)) {
            isVirtual = 1;
            advance();
        }
        advance();
        Node *Callee = new IdentifierNode(peek());
        except(TokenTypes::IDENTIFIER);
        except(TokenTypes::LEFT_PAREN);
        except(TokenTypes::RIGHT_PAREN);
        int isAbs = 0;
        Node *Block = new EmptyNode();
        if (check(TokenTypes::EQUAL)) {
            advance();
            except(TokenTypes::DEFAULT);
            isAbs = 1;
        } else
            Block = parseBlock();
        DestructorNode *Destructor = new DestructorNode(Callee, isAbs, isVirtual);
        (*Destructor).body(Block);
        return Destructor;
    }

    Node *parseMemberInitializer() {
        Node *name = new IdentifierNode(peek());
        except(TokenTypes::IDENTIFIER);
        except(TokenTypes::LEFT_PAREN);
        Node *Value = parseExpression();
        except(TokenTypes::RIGHT_PAREN);
        return new MemberInitializer(name, Value);
    }

    void parseObject(int isClass = 0, Node *target = new EmptyNode()) {
        Block *block = new Block();
        int isDefaultPublic = ((isClass) ? 0 : 1);
        int Current = isDefaultPublic;
        if (except(TokenTypes::LEFT_BRACE)) {
            while (peek().type != TokenTypes::RIGHT_BRACE) {
                Node *stmt = parseStatment(0, 1);
                if (getName(stmt) == "PublicNode") {
                    if (!Current)
                        Current = !Current;
                } else if (getName(stmt) == "PrivateNode") {
                    if (Current)
                        Current = !Current;
                } else if (getName(stmt) == "VariableDeclarationNode") {
                    stmt = new FieldDeclaration(stmt);
                    if (isClass) {
                        if (Current) (*(ClassDeclaration *) target).addPublicField(stmt);
                        else (*(ClassDeclaration *) target).addPrivateField(stmt);
                    } else {
                        if (Current) (*(StructDeclaration *) target).addPublicField(stmt);
                        else (*(StructDeclaration *) target).addPrivateField(stmt);
                    }
                } else if (getName(stmt) == "Constructor") {
                    if (isClass) (*(ClassDeclaration *) target).constructor(stmt);
                    else (*(StructDeclaration *) target).constructor(stmt);
                } else if (getName(stmt) == "Destructor") {
                    if (isClass) (*(ClassDeclaration *) target).destructor(stmt);
                    else (*(StructDeclaration *) target).destructor(stmt);
                } else if (getName(stmt) == "MethodStatment") {
                    if (isClass) (*(ClassDeclaration *) target).addMethod(stmt);
                    else (*(StructDeclaration *) target).addMethod(stmt);
                }
                if (peek().type == TokenTypes::SEMICOLON)
                    advance();
            }
            except(TokenTypes::RIGHT_BRACE);
        }
    }

    Node *parsePublicNode() {
        advance();
        if (!check(TokenTypes::IDENTIFIER))
            except(TokenTypes::DOUBLE_POINTS);
        return new PublicNode;
    }

    Node *parsePrivateNode() {
        advance();
        if (!check(TokenTypes::IDENTIFIER))
            except(TokenTypes::DOUBLE_POINTS);
        return new PrivateNode;
    }

    Node *parseStructStatment() {
        advance();
        Node *Name = new IdentifierNode(peek());
        except(TokenTypes::IDENTIFIER);
        StructDeclaration *Struct = new StructDeclaration(Name);
        addObject((*(IdentifierNode *) Name).val.value);
        parseObject(0, Struct);

        return Struct;
    }

    Node *parseClassStatment() {
        advance();
        Node *Name = new IdentifierNode(peek());
        except(TokenTypes::IDENTIFIER);
        ClassDeclaration *Class = new ClassDeclaration(Name);
        parseObject(1, Class);
        addObject((*(IdentifierNode *) Name).val.value);
        return Class;
    }

    Node *parseAddressOfNode() {
        advance();
        Node *expression = parseExpression();
        return new AddressNode(expression);
    }

    Node *parseDereferenceNode() {
        advance();
        Node *expression = parseLogicalOr();
        return new DereferenceNode(expression);
    }

    Node* parseNewNode() {
        advance();
        Token type = peek();
        advance();
        if (check(TokenTypes::LEFT_PAREN)) {
            advance();

            vector<Node *> Args;

            while (!check(TokenTypes::RIGHT_PAREN)) {
                if (isType(peek().type)&&position+1<tokens.size()&&tokens[position+1].type==TokenTypes::IDENTIFIER)
                    Args.push_back(parseVariableDeclaration());
                else
                    Args.push_back(parseExpression());

                if (check(TokenTypes::COMMA))
                    advance();
                else
                    break;
            }

            except(TokenTypes::RIGHT_PAREN);

            NewNode* node = new NewNode(type);
            for (Node *arg: Args)
                (*node).addArg(arg);

            return node;
        }
        return new NewNode(type);
    }
    Node* parseTypeRelatedExpressions() {
        Token current = peek();
        advance();

        if (except(TokenTypes::LEFT_PAREN)) {
            vector<Node *> Args;

            if (isType(peek().type)||isObject()) {
                Token type=peek();
                advance();
                Node* Type=new EmptyNode;
                int isProp = 0;
                if (check(TokenTypes::MULTIPLY)) {
                    Type = new PointerType(type);
                    isProp = 1;
                    advance();
                } else if (check(TokenTypes::POWER)) {
                    int ptrs = 2;
                    advance();
                    while (check(TokenTypes::POWER) || check(TokenTypes::MULTIPLY)) {
                        if (check(TokenTypes::MULTIPLY))
                            ptrs++;
                        else
                            ptrs += 2;
                        advance();
                    }
                    Node *ptr = new PointerType(type);
                    for (int i = 0; i < ptrs - 1; i++) {
                        ptr = new PointerType(type, 1, ptr);
                    }
                    Type = ptr;
                    isProp = 1;
                }
                except(TokenTypes::RIGHT_PAREN);
                TypeRelatedNode* node = nullptr;
                if (current.value=="sizeof")
                    node = new SizeOfTypeNode(type,isProp,Type);
                return node;
            }else {
                Node* expression = parseExpression();
                except(TokenTypes::RIGHT_PAREN);
                ExpressionRelatedNode* node = nullptr;
                if (current.value=="sizeof")
                    node = new SizeOfExpressionnode(expression);
                return node;
            }
        }
        return new EmptyNode();
    }

    Node *parseStatment(int loop = 0, int object = 0) {
        if (isType(peek().type))
            return parseVariableDeclaration();
        if (peek().type == TokenTypes::IF)
            return parseIfStatment(loop);
        if (peek().type == TokenTypes::WHILE)
            return parseWhileStatment(loop + 1);
        if (peek().type == TokenTypes::BREAK)
            return parseBreakStatment();
        if (peek().type == TokenTypes::CONTINUE)
            return parseContinueStatment();
        if (peek().type == TokenTypes::FOR)
            return parseForStatment(loop + 1);
        if (peek().type == TokenTypes::RETURN)
            return parseReturnStatment();
        if (check(TokenTypes::VIRTUAL) && position + 1 < tokens.size() && tokens[position + 1].type == TokenTypes::SEA)
            return parseDestructor();
        if ((peek().type == TokenTypes::FUNCTION) || (
                (peek().type == TokenTypes::VIRTUAL || peek().type == TokenTypes::OVERRIDE || peek().type ==
                 TokenTypes::FRIEND || peek().type == TokenTypes::STATIC) && object))
            return parseFunction(object);
        if (peek().type == TokenTypes::SEA)
            return parseDestructor();
        if (peek().type == TokenTypes::STRUCT)
            return parseStructStatment();
        if (peek().type == TokenTypes::PUBLIC)
            return parsePublicNode();
        if (peek().type == TokenTypes::PRIVATE)
            return parsePrivateNode();
        if (peek().type == TokenTypes::CLASS)
            return parseClassStatment();

        if (isObject() && position + 1 < tokens.size()) {
            if (tokens[position + 1].type == TokenTypes::LEFT_PAREN) {
                if (object) {
                    return parseCalleeExpression(1, new IdentifierNode(peek()));
                }
            } else {
                return parseVariableDeclaration(1);
            }
        }


        return parseExpressionStatment();
    }


    Node *parseProgram() {
        Program *program = new Program();
        while (peek().type != TokenTypes::END_OF_FILE) {
            Node *stmt = parseStatment();
            (*program).addNode(stmt);
            if (peek().type == TokenTypes::SEMICOLON)
                advance();

            else if (isBrace(stmt))
                throw std::runtime_error(
                    "Expected ';' after expression Type: " + tokenTypeToString(peek().type) + " value: " + peek().value
                    + "Line: " + to_string(peek().line) + "Col: " + to_string(peek().column));
        }
        if (peek().type == TokenTypes::END_OF_FILE)
            cout << endl
                    << "End Of File Reached!!";
        return program;
    }
};

string ASTString(Node *node) {
    if (node == nullptr) return "NullNode";

    if (dynamic_cast<LiteralNode *>(node))
        return "LiteralNode";
    if (dynamic_cast<IdentifierNode *>(node))
        return "IdentifierNode";
    if (dynamic_cast<BinaryNode *>(node))
        return "BinaryNode";
    if (dynamic_cast<UnaryNode *>(node))
        return "UnaryNode";
    if (dynamic_cast<ExpressionStatment *>(node))
        return "ExpressionStatment";
    if (dynamic_cast<VariableDeclarationNode *>(node))
        return "VariableDeclarationNode";
    if (dynamic_cast<Initializer *>(node))
        return "Initializer";
    if (dynamic_cast<EmptyNode *>(node))
        return "EmptyNode";
    if (dynamic_cast<IfStatment *>(node))
        return "IfStatment";
    if (dynamic_cast<ElseIfStatment *>(node))
        return "ElseIfStatment";
    if (dynamic_cast<ElseStatment *>(node))
        return "ElseStatment";
    if (dynamic_cast<WhileStatment *>(node))
        return "WhileStatment";
    if (dynamic_cast<ReturnStatment *>(node))
        return "ReturnStatment";
    if (dynamic_cast<Condition *>(node))
        return "Condition";
    if (dynamic_cast<Block *>(node))
        return "Block";
    if (dynamic_cast<ForStatment *>(node))
        return "ForStatment";

    return "UnknownNode";
}

class Symbol {
public:
    string name;
    TokenTypes type;
    string Kind;

    Symbol(string n, TokenTypes t, string k) : Kind(k), type(t), name(n) {
    }
};

class SymbolTable {
public:
    vector<Symbol> symbols;

    void addSymbol(Symbol hihi) {
        symbols.push_back(hihi);
    }

    int contains(string name) {
        for (const Symbol &s: symbols) {
            if (s.name == name)
                return 1;
        }
        return 0;
    }

    Symbol lookup(string name) {
        for (const Symbol &s: symbols) {
            if (s.name == name)
                return s;
        }
        return Symbol("", TokenTypes::UNKNOWN, "");
    }
};

string toString(string filename) {
    ifstream file(filename);
    if (!file.is_open())
        return "Not Found";

    string line;
    string content = "";

    while (getline(file, line)) {
        content += line + "\n";
    }

    return content;
}


int main(int argc, char *argv[]) {
    auto start = chrono::high_resolution_clock::now();
    string filename = argv[1];
    string source = toString(filename);
    cout << "Source is: " << endl
            << source << endl;
    if (source == "Not Found") {
        cout << "File Not Found!" << endl;
        return 1;
    }
    Lexer lexer(source);
    vector<Token> tokens = lexer.tokenize();
    for (const Token &t: tokens) {
        cout << endl
                << tokenTypeToString(t.type);
    }
    Parser parser(tokens);
    Node *shiit = parser.parseProgram();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    (*shiit).print(0);
    cout << endl
            << endl
            << "Duration is: " << duration.count();
    return 0;
}
