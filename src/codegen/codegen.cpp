#include "codegen.hpp"

#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "parser/parser.hpp"
#include "utils/exceptions.hpp"
#include "utils/string.hpp"

using namespace std;
using namespace codegen;

/* -------------------------------------------------------------------------- */

Mov::Mov(shared_ptr<parser::Return> ret) {
    if (auto constant = dynamic_cast<parser::Constant*>(ret->exp.get())) {
        src = make_unique<Imm>(constant->value);
    } else {
        throw CodegenError("unsupported mov type");
    }

    dst = make_unique<Register>(reg::EAX);
}

Imm::Imm(string val) : val(val) {}

Register::Register(reg::Type type) : type(type) {}

Function::Function(shared_ptr<parser::FunctionDef> func) : name(func->name) {
    if (auto ret = dynamic_pointer_cast<parser::Return>(func->body)) {
        instructions.push_back(make_shared<Mov>(ret));
        instructions.push_back(make_shared<Ret>());
    }
}

Program::Program(shared_ptr<parser::Program> prog) {
    function_def = make_shared<Function>(prog->function);
}

/* -------------------------------------------------------------------------- */

string Ret::toString() { return "ret"; }

string Mov::toString() {
    return "movl " + src->toString() + ", " + dst->toString();
}

string Imm::toString() { return "$" + val; }

string Register::toString() { return "%" + reg::toString(type); }

string Function::toString() {
    string str = "_" + name + ":";
    for (auto& inst : instructions) {
        str += "\n" + inst->toString();
    }
    return str;
}

string Program::toString() { return function_def->toString(); }

/* -------------------------------------------------------------------------- */

asm_ast::asm_ast(unique_ptr<parser::Program> parser_ast)
    : parser_ast(std::move(parser_ast)) {}

unique_ptr<Program> asm_ast::Parse() {
    return make_unique<Program>(std::move(parser_ast));
}

void codegen::EmitAsm(string filename, unique_ptr<Program> prog) {
    std::ofstream out(filename);

    if (!out) {
        CodegenError("failed to open file \"" + filename + "\"");
    }

    auto function = prog->function_def;

    out << util::repeatTabs(1) + ".globl _" + function->name;
    out << "\n_" + function->name + ":";
    for (auto instr : function->instructions) {
        out << "\n" + util::repeatTabs(1) + instr->toString();
    }
}