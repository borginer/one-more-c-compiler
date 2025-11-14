#include "lexer/lexer.hpp"

#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool isDigit(char c) { return c >= '0' && c <= '9'; }

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

unordered_map<string, TokenType> KEYWORDS = {
    {"return", RETURN}, {"int", INT}, {"void", VOID}};

Lexer::Lexer(string input) : input(input) { cout << input << endl; }

void Lexer::addToken(TokenType tt, string val) {
    tokens.push_back(Token(tt, val, line));
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
    addToken(NUMBER, numStr);
}

void Lexer::scanAlpha() {
    while (isAlpha(peek())) {
        step();
    }
    string name = input.substr(start, index - start);
    if (KEYWORDS.count(name)) {
        addToken(KEYWORDS[name]);
    } else {
        addToken(IDENTIFIER, name);
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
            addToken(OPEN_PARENTH);
            break;
        case '}':
            addToken(CLOSE_PARENTH);
            break;
        case '(':
            addToken(OPEN_BRACE);
            break;
        case ')':
            addToken(CLOSE_BRACE);
            break;
        case ';':
            addToken(SEMICOLON);
            break;
        default:
            if (isDigit(c)) {
                scanNumber();
            } else if (isAlpha(c)) {
                scanAlpha();
            } else {
                cerr << "unexpected token on line: " + to_string(line) << endl;
                exit(2);
            }
            break;
    }
}

vector<Token> Lexer::Lex() {
    while (!isAtEnd()) {
        start = index;
        scanToken();
    }
    addToken(_EOF);
    return tokens;
}

void Lexer::PrintTokens() {
    string tab = "  ";
    size_t scope = 0;

    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].type == OPEN_PARENTH) {
            scope++;
        } else if (tokens[i].type == CLOSE_PARENTH) {
            scope--;
        } else if (tokens[i].type == _EOF) {
            cout << '\n';
            return;
        }

        if (i > 0 && tokens[i].line != tokens[i - 1].line) {
            cout << '\n';
            for (size_t i = 0; i < scope; i++) {
                cout << tab;
            }
        }
        cout << tokens[i].toString() + " ";
    }
}
