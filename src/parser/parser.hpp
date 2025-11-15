#pragma once

#include <memory>
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
    std::vector<std::unique_ptr<Node>> children;
    std::string value;
    std::string name;

    Node(Type type);
    std::string toString();
};

class AST {
    size_t index = 0;
    size_t scope = 0;
    std::vector<token::Token> tokens;

    const token::Token& expect(token::Type type);
    std::unique_ptr<Node> parseFunctionDef();
    std::unique_ptr<Node> parseStatement();
    std::unique_ptr<Node> parseExp();
    std::string parseInt();
    std::string parseIdentifier();
    void printProgram(std::unique_ptr<Node>& node);

   public:
    AST(std::vector<token::Token> tokens);
    std::unique_ptr<Node> ParseProgram();
    void PrintProgram(std::unique_ptr<Node>& treeHead);
};
}  // namespace ast
