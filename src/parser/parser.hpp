#pragma once

#include <string>
#include <vector>

#include "token/token.hpp"

namespace ast {
enum Type {
    PROGRAM,
    FUNCTION_DEF,
    STATEMENT,
    EXP,
    IDENTIFIER,
    INT,
};

class Node {
   public:
    Type type;
    std::vector<Node*> children;
    std::string value;
    std::string name;

    Node(Type type);
    std::string toString();
};

class AST {
    size_t index = 0;
    size_t scope = 0;
    std::vector<token::Token> tokens;
    Node* tree_head;

    token::Token& expect(token::Type type);
    Node* parseFunctionDef();
    Node* parseStatement();
    Node* parseExp();
    std::string parseInt();
    std::string parseIdentifier();
    void printProgram(Node* node);

   public:
    AST(std::vector<token::Token> tokens);
    Node* ParseProgram();
    void PrintProgram();
};
}  // namespace ast
