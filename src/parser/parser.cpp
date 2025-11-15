#include "parser.hpp"

#include <cstddef>
#include <iostream>

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

AST::AST(vector<token::Token> tokens) : tokens(tokens) {}

token::Token& AST::expect(token::Type type) {
    if (index < tokens.size() && tokens[index].type == type) {
        index++;
        return tokens[index - 1];
    } else {
        cerr << "unexpected token: " << tokens[index].toString() << endl;
        exit(3);
    }
}

Node* AST::parseFunctionDef() {
    expect(token::INT);
    string identifier = expect(token::IDENTIFIER).value;
    expect(token::OPEN_BRACE);
    expect(token::VOID);
    expect(token::CLOSE_BRACE);
    expect(token::OPEN_PARENTH);
    Node* statement = parseStatement();
    expect(token::CLOSE_PARENTH);

    Node* function_def = new Node(FUNCTION_DEF);
    function_def->children.push_back(statement);
    function_def->name = identifier;
    return function_def;
}

Node* AST::parseStatement() {
    expect(token::RETURN);
    Node* exp = parseExp();
    expect(token::SEMICOLON);

    Node* statement = new Node(STATEMENT);
    statement->value = "return";
    statement->children.push_back(exp);
    return statement;
}

Node* AST::parseExp() {
    string constant = parseInt();

    Node* exp = new Node(EXP);
    exp->value = constant;
    return exp;
}

string AST::parseInt() { return expect(token::NUMBER).value; }

string AST::parseIdentifier() { return expect(token::IDENTIFIER).value; }

Node* AST::ParseProgram() {
    tree_head = new Node(PROGRAM);
    tree_head->children.push_back(parseFunctionDef());
    return tree_head;
}

void AST::PrintProgram() { AST::printProgram(tree_head); }

void AST::printProgram(Node* node) {
    string tab = "   ";

    for (size_t i = 0; i < scope; i++) {
        cout << tab;
    }
    cout << node->toString() << endl;

    scope++;
    for (Node* child : node->children) {
        printProgram(child);
    }
    scope--;
}