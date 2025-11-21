#include "parser.hpp"

#include <cstddef>
#include <memory>
#include <string>

#include "token/token.hpp"
#include "utils/string.hpp"

using namespace std;
using namespace parser;

/* -------------------------------------------------------------------------- */

Constant::Constant(token::Tokens& tokens) {
    value = tokens.expect(token::NUMBER).value;
}

Return::Return(token::Tokens& tokens) {
    tokens.expect(token::RETURN);
    exp = make_shared<Constant>(tokens);
    tokens.expect(token::SEMICOLON);
}

FunctionDef::FunctionDef(token::Tokens& tokens) {
    tokens.expect(token::INT);
    name = tokens.expect(token::IDENTIFIER).value;
    tokens.expect(token::OPEN_BRACE);
    tokens.expect(token::VOID);
    tokens.expect(token::CLOSE_BRACE);
    tokens.expect(token::OPEN_PARENTH);
    body = make_shared<Return>(tokens);
    tokens.expect(token::CLOSE_PARENTH);
}

Program::Program(token::Tokens& tokens) {
    function = make_shared<FunctionDef>(tokens);
}

/* -------------------------------------------------------------------------- */

string Constant::toString(size_t scope) {
    return util::repeatTabs(scope) + "Constant(" + this->value + ")";
}

string Return::toString(size_t scope) {
    string str = "Return(";
    str += "\n" + this->exp->toString(scope + 1);
    str += "\n" + util::repeatTabs(scope) + ")";
    return str;
}

string FunctionDef::toString(size_t scope) {
    string str = util::repeatTabs(scope) + "Function(";
    str += "\n" + util::repeatTabs(scope + 1) + "name=" + this->name;
    str += "\n" + util::repeatTabs(scope + 1) +
           "body=" + this->body->toString(scope + 1);
    str += "\n" + util::repeatTabs(scope) + ")";
    return str;
}

string Program::toString(size_t scope) {
    string str = util::repeatTabs(scope) + "Program(";
    str += "\n" + this->function->toString(scope + 1);
    str += "\n" + util::repeatTabs(scope) + ")";
    return str;
}

/* -------------------------------------------------------------------------- */

ast::ast(vector<token::Token> tokens) : tokens(std::move(tokens)) {}

unique_ptr<Program> ast::ParseProgram() {
    return make_unique<Program>(this->tokens);
}
