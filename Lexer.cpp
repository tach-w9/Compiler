#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

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
    END_OF_FILE
};
struct Token
{
    TokenTypes type;
    string value;
    int column = 0;
    int line = 0;
};
class Lexer
{
private:
    string src;
    int position = 0;
    int column, line = 0;

public:
    Lexer(const string &src) : src(src) {}
    char current(){
        return src[position];
    }
};
