#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include "TokenType.h"

struct Token {
  TokenType type;
  std::string lexeme;
  int line;

  std::string toString() {
    return type + " " + lexeme + " ";
  }
};

#endif // TOKEN_H
