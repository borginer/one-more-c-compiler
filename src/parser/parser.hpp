#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "token/token.hpp"

namespace ast {

class Node {
   public:
    virtual ~Node() = default;
    virtual std::string toString(size_t scope) = 0;
};

struct Exp : public Node {};

struct Constant : public Exp {
    std::string value;

   public:
    Constant(token::Tokens& tokens);
    std::string toString(size_t scope) override;
};

struct Statement : public Node {};

class Return : public Statement {
    std::unique_ptr<Exp> exp;

   public:
    Return(token::Tokens& tokens);
    std::string toString(size_t scope) override;
};

class FunctionDef : public Node {
    std::string name;
    std::unique_ptr<Statement> body;

   public:
    FunctionDef(token::Tokens& tokens);
    std::string toString(size_t scope) override;
};

class Program : public Node {
    std::unique_ptr<FunctionDef> function;

   public:
    Program(token::Tokens& tokens);
    std::string toString(size_t scope) override;
};

class AST {
    token::Tokens tokens;

   public:
    AST(std::vector<token::Token> tokens);
    std::unique_ptr<Program> ParseProgram();
};
}  // namespace ast
