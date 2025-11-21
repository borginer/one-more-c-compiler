#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "token/token.hpp"

namespace parser {

struct Node {
   public:
    virtual ~Node() = default;
    virtual std::string toString(size_t scope) = 0;
};

struct Exp : public Node {};

struct Statement : public Node {};

struct Constant : public Exp {
    std::string value;
    Constant(token::Tokens& tokens);
    std::string toString(size_t scope) override;
};


struct Return : public Statement {
    std::shared_ptr<Exp> exp;
    Return(token::Tokens& tokens);
    std::string toString(size_t scope) override;
};

struct FunctionDef : public Node {

std::string name;
    std::shared_ptr<Statement> body;
    FunctionDef(token::Tokens& tokens);
    std::string toString(size_t scope) override;
};

struct Program : public Node {
    std::shared_ptr<FunctionDef> function;

    Program(token::Tokens& tokens);
    std::string toString(size_t scope = 0) override;
};

class ast {
    token::Tokens tokens;

   public:
    ast(std::vector<token::Token> tokens);
    std::unique_ptr<Program> ParseProgram();
};
}  // namespace parser
