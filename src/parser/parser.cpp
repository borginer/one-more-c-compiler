#include "parser.hpp"

#include <cstddef>
#include <iostream>
#include <memory>

#include "token/token.hpp"

using namespace std;
using namespace ast;

Node::Node(Type type) : type(type) {}

string Node::toString() {
    switch (type) {
        case PROGRAM:
            return "PROGRAM";
            break;
        case FUNCTION_DEF:
            return "FUNCTION_DEF: " + name;
            break;
        case STATEMENT:
            return "STATEMENT: " + value;
            break;
        case EXP:
            return "EXP: " + value;
            break;
        default:
            cerr << "unsupported Node type" << endl;
            exit(5);
            break;
    }
}

AST::AST(vector<token::Token> tokens) : tokens(std::move(tokens)) {}

const token::Token& AST::expect(token::Type type) {
    if (index < tokens.size() && tokens[index].type == type) {
        index++;
        return tokens[index - 1];
    } else {
        cerr << "unexpected token: " << tokens[index].toString() << " on line "
             << tokens[index].line << endl;
        exit(3);
    }
}

unique_ptr<Node> AST::parseFunctionDef() {
    auto function_def = make_unique<Node>(FUNCTION_DEF);

    expect(token::INT);
    function_def->name = expect(token::IDENTIFIER).value;
    expect(token::OPEN_BRACE);
    expect(token::VOID);
    expect(token::CLOSE_BRACE);
    expect(token::OPEN_PARENTH);
    function_def->children.push_back(parseStatement());
    expect(token::CLOSE_PARENTH);
    return function_def;
}

unique_ptr<Node> AST::parseStatement() {
    auto statement = make_unique<Node>(STATEMENT);
    statement->value = "return";

    expect(token::RETURN);
    statement->children.push_back(parseExp());
    expect(token::SEMICOLON);
    return statement;
}

unique_ptr<Node> AST::parseExp() {
    auto exp = make_unique<Node>(EXP);
    exp->value = parseInt();
    return exp;
}

string AST::parseInt() { return expect(token::NUMBER).value; }

string AST::parseIdentifier() { return expect(token::IDENTIFIER).value; }

unique_ptr<Node> AST::ParseProgram() {
    auto tree_head = make_unique<Node>(PROGRAM);
    tree_head->children.push_back(parseFunctionDef());
    return tree_head;
}

void AST::PrintProgram(unique_ptr<Node>& treeHead) {
    AST::printProgram(treeHead);
}

void AST::printProgram(unique_ptr<Node>& node) {
    string tab = "   ";

    for (size_t i = 0; i < scope; i++) {
        cout << tab;
    }
    cout << node->toString() << endl;

    scope++;
    for (auto& child : node->children) {
        printProgram(child);
    }
    scope--;
}