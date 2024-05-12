#ifndef LOX_H
#define LOX_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Lox {
private:
  static bool hadError;
  static void report(int line, const std::string& where, const std::string& message);

public:
  static void runFile(const std::string& path);
  static void runPrompt();
  static void run(const std::string& source);
  static void error(int line, const std::string& message);
};

#endif // LOX_H
