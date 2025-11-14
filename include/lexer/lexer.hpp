#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "common/token.hpp"

class Lexer {
    size_t index = 0;
    size_t start = 0;
    size_t line = 15;
    std::string input;
    std::vector<Token> tokens;

    void addToken(TokenType tt, std::string val = "");
    bool isAtEnd();
    char step();
    char peek();
    void scanAlpha();
    void scanNumber();
    void scanToken();

   public:
    Lexer(std::string input);
    std::vector<Token> Lex();
    void PrintTokens();
};
