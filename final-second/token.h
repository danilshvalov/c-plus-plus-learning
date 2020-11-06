
#include <sstream>
#include <vector>
using namespace std;

#ifndef __TOKEN_H__
#define __TOKEN_H__
enum class TokenType {
    DATE,
    EVENT,
    COLUMN,
    LOGICAL_OP,
    COMPARE_OP,
    PAREN_LEFT,
    PAREN_RIGHT,
};

struct Token {
    const string value;
    const TokenType type;
};

vector<Token> Tokenize(istream& cl);
#endif // __TOKEN_H__