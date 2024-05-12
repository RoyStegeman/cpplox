#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include "TokenType.h"

class Token {
private:
  TokenType type;
  int line;

public:
  std::string lexeme;
  std::string toString();
  Token(const TokenType type, const std::string lexeme, int line);
};

#endif // TOKEN_H
