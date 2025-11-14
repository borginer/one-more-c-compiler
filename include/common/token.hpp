#pragma once

#include <string>

enum TokenType {
    // single char tokens
    OPEN_BRACE,
    CLOSE_BRACE,
    OPEN_PARENTH,
    CLOSE_PARENTH,
    SEMICOLON,
    // keywords
    RETURN,
    INT,
    VOID,
    // literals
    IDENTIFIER,
    NUMBER,
    // other
    _EOF
};

class Token {
   public:
    TokenType type;
    std::string value;
    std::size_t line;

    Token(TokenType tt, std::string val, size_t line);
    std::string toString();
};