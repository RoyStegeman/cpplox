#include "Token.h"

Token::Token(const TokenType type, const std::string lexeme, int line){};

std::string Token::toString() {
    return type + " " + lexeme + " ";
}

