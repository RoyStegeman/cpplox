#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <vector>
#include <map>

#include "Token.h"
#include "TokenType.h"

class Scanner {
private:
  std::string source;
  std::vector<Token> tokens;
  static std::map<std::string, TokenType> keywords;
  int start = 0;
  int current = 0;
  int line = 1;
  void scanToken();
  void identifier();
  void number();
  void string();
  bool isDigit(char c);
  char peek();
  char peekNext();
  bool isAlpha(char c);
  bool isAlphaNumeric(char c);
  bool isAtEnd();
  char advance();
  void addToken(TokenType type);


public:
  Scanner(const std::string& source);
  std::vector<Token> scanTokens();
};

#endif // SCANNER_H
