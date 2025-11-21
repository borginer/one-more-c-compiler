#include "token.hpp"

#include <string>

#include "utils/exceptions.hpp"

using namespace std;
using namespace token;

string Token::toString() const {
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

Tokens::Tokens(vector<token::Token> tokens) : tokens(std::move(tokens)) {}

const token::Token& token::Tokens::expect(token::Type type) {
    if (index < tokens.size() && tokens[index].type == type) {
        index++;
        return tokens[index - 1];
    } else {
        throw LexerError("unexpected token " + tokens[index].toString() +
                         " on line " + to_string(tokens[index].line));
    }
}