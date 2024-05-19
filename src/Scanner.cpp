#include "Scanner.h"
#include "Lox.h"

Scanner::Scanner(const std::string &source) : source(source) {}

std::vector<Token> Scanner::scanTokens()
{
  while (!isAtEnd())
  {
    // We are at the beginning of the next lexeme.
    start = current;
    scanToken();
  }

  // once we finished reading the file add END_OF_FILE
  tokens.push_back(Token(END_OF_FILE, "", line));
  return tokens;
}

void Scanner::scanToken() {
  char c = advance();
  switch (c) {
  case '(': addToken(LEFT_PAREN); break;
  case ')': addToken(RIGHT_PAREN); break;
  case '{': addToken(LEFT_BRACE); break;
  case '}': addToken(RIGHT_BRACE); break;
  case ',': addToken(COMMA); break;
  case '.': addToken(DOT); break;
  case '-': addToken(MINUS); break;
  case '+': addToken(PLUS); break;
  case ';': addToken(SEMICOLON); break;
  case '*': addToken(STAR); break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG);
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL);
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS);
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER);
    break;

  // '/' needs more care since comments start with / as well
  case '/':
    if (match('/')) {
      // A comment goes until the end of the line.
      while (peek() != '\n' && !isAtEnd()) advance();
    } else if (match('*')) {
      /* A C-style comment can span multiple lines */
      while (peek() != '*') advance();
      while (peek() != '/') advance();
      advance();
    } else {
      addToken(SLASH);
    }
    break;

  // characters to ignore
  case ' ':
  case '\r':
  case '\t':
    break;

  case '\n':
    line++;
    break;

  case '"': string(); break;

  default:
    if (isDigit(c)) {
      number();
    } else if (isAlpha(c)) {
      identifier();
    } else {
      Lox::error(line, "Unexpected character.");
    }
    break;

  }
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek())) advance();
  addToken(IDENTIFIER);
}

void Scanner::number() {
  while (isDigit(peek())) advance();

  // Look for a fractional part
  if (peek() == '.' && isDigit(peekNext())) {
    // consume the "."
    advance();

    while (isDigit(peek())) advance();
  }

  // TODO: pass value of the number
  addToken(NUMBER);
}

void Scanner::string() {
  // continue parsing the string until we encounter '"'
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    advance();
  }

  // if we don't encounter '"' before the end of the line, something went wrong
  if (isAtEnd()) {
    Lox::error(line, "Unterminated string.");
    return;
  }

  // parse the closing '"'
  advance();

  // remove the quotes to be left with only the string
  std::string value = source.substr(start+1, current-start-1);
  // TODO: pass 'value' to addToken
  addToken(STRING);
}

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (source[current] != expected) return false;
  current++;
  return true;
}

char Scanner::peek () {
  if (isAtEnd()) return '\0';
  return source[current];
}

char Scanner::peekNext() {
  if (current + 1 >= source.length()) return '\0';
  return source[current+1];
}

bool Scanner::isAlphaNumeric(char c) {
  return isAlpha(c) || isDigit(c);
}

bool Scanner::isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::isDigit(char c) {
  return c >= '0' && c <= '9';
}

bool Scanner::isAtEnd() {
  return current >= source.length();
}

char Scanner::advance() {
  return source[current++];
}

void Scanner::addToken(TokenType type) {
  std::string text = source.substr(start,current-start);
  tokens.push_back(Token(type, text, line));
}
