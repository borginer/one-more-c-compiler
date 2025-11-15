#pragma once

#include <string>

namespace token {
enum Type {
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

struct Token {
    Type type;
    std::string value;
    std::size_t line;

    std::string toString() const;
};
}  // namespace token
