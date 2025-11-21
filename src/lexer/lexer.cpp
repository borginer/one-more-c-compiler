#include "lexer.hpp"

#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/exceptions.hpp"
#include "utils/string.hpp"

using namespace std;
using namespace lexer;

bool isDigit(char c) { return c >= '0' && c <= '9'; }

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

unordered_map<string, token::Type> KEYWORDS = {
    {"return", token::RETURN}, {"int", token::INT}, {"void", token::VOID}};

Lexer::Lexer(string input) : input(input) {}

void Lexer::addToken(token::Type tt, string val) {
    tokens.emplace_back(tt, val, line);
}

bool Lexer::isAtEnd() { return index >= input.size(); }

char Lexer::step() {
    if (!isAtEnd()) {
        index++;
        return input[index - 1];
    }
    return '\0';
}

char Lexer::peek() {
    if (!isAtEnd()) {
        return input[index];
    }
    return '\0';
}

void Lexer::scanNumber() {
    while (isDigit(peek())) {
        step();
    }
    string numStr = input.substr(start, index - start);
    addToken(token::NUMBER, numStr);
}

void Lexer::scanAlpha() {
    while (isAlpha(peek())) {
        step();
    }
    string name = input.substr(start, index - start);
    if (KEYWORDS.count(name)) {
        addToken(KEYWORDS[name]);
    } else {
        addToken(token::IDENTIFIER, name);
    }
}

void Lexer::scanToken() {
    char c = step();
    switch (c) {
        case '\t':
        case ' ':
            // skip whitespace
            break;
        case '\n':
            line++;
            break;
        case '{':
            addToken(token::OPEN_PARENTH);
            break;
        case '}':
            addToken(token::CLOSE_PARENTH);
            break;
        case '(':
            addToken(token::OPEN_BRACE);
            break;
        case ')':
            addToken(token::CLOSE_BRACE);
            break;
        case ';':
            addToken(token::SEMICOLON);
            break;
        default:
            if (isDigit(c)) {
                scanNumber();
            } else if (isAlpha(c)) {
                scanAlpha();
            } else {
                throw LexerError("unexpected character '" + string(1, c) + "'" +
                                 " on line: " + to_string(line));
            }
            break;
    }
}

vector<token::Token> Lexer::Lex() {
    while (!isAtEnd()) {
        start = index;
        scanToken();
    }
    addToken(token::_EOF);
    return tokens;
}

void Lexer::PrintTokens() {
    size_t scope = 0;

    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].type == token::OPEN_PARENTH) {
            scope++;
        } else if (tokens[i].type == token::CLOSE_PARENTH) {
            scope--;
        } else if (tokens[i].type == token::_EOF) {
            cout << '\n';
            return;
        }

        if (i > 0 && tokens[i].line != tokens[i - 1].line) {
            cout << '\n';
            cout << util::repeatTabs(scope);
        }
        cout << tokens[i].toString() + " ";
    }
}
