#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "parser/parser.hpp"
#include "register/register.hpp"

namespace codegen {

struct Node {
   public:
    virtual ~Node() = default;
    virtual std::string toString() = 0;
};

struct Instruction : public Node {};

struct Operand : public Node {};

struct Ret : public Instruction {
   public:
    std::string toString() override;
};

struct Mov : public Instruction {
    std::unique_ptr<Operand> src, dst;

   public:
    Mov(std::shared_ptr<parser::Return> ret);
    std::string toString() override;
};

struct Imm : public Operand {
    std::string val;

   public:
    Imm(std::string val);
    std::string toString() override;
};

struct Register : public Operand {
    reg::Type type;

   public:
    Register(reg::Type type);
    std::string toString() override;
};

struct Function : public Node {
    std::string name;
    std::vector<std::shared_ptr<Instruction>> instructions;

   public:
    Function(std::shared_ptr<parser::FunctionDef> func);
    std::string toString() override;
};

struct Program : public Node {
    std::shared_ptr<Function> function_def;

   public:
    Program(std::shared_ptr<parser::Program> prog);
    std::string toString() override;
};

class ast {
    std::shared_ptr<parser::Program> parser_ast;

   public:
    ast(std::unique_ptr<parser::Program> parser_ast);
    std::unique_ptr<Program> AsmProgram();
};
}  // namespace codegen
