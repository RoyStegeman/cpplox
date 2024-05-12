#include "Lox.h"
#include "Scanner.h"

bool Lox::hadError = false;

void Lox::runFile(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    run(buffer.str());
}

void Lox::runPrompt() {
    std::string line;
    for (;;) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line.empty()) break;
        run(line);
    }
}

void Lox::run(const std::string& source) {
    Scanner scanner(source);
    auto tokens = scanner.scanTokens();

    // For now, just print the tokens.
    for (const auto& token : tokens) {
        std::cout << token.lexeme << std::endl;
    }
}

void Lox::error(int line, const std::string& message) {
    report(line, "", message);
}

void Lox::report(int line, const std::string& where, const std::string& message) {
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    hadError = true;
}
