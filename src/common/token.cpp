#include "common/token.hpp"

using namespace std;

Token::Token(TokenType tt, string value, size_t line)
    : type(tt), value(value), line(line) {}

string Token::toString() {
    switch (type) {
        case OPEN_BRACE:
            return "(";
        case CLOSE_BRACE:
            return ")";
        case OPEN_PARENTH:
            return "{";
        case CLOSE_PARENTH:
            return "}";
        case SEMICOLON:
            return ";";
        case RETURN:
            return "RETURN";
        case INT:
            return "INT";
        case VOID:
            return "VOID";
        case IDENTIFIER:
            return "IDENTIFIER:" + value;
        case NUMBER:
            return "NUMBER:" + value;
        case _EOF:
            return "EOF";
        default:
            return "not implemented yet";
    }
}