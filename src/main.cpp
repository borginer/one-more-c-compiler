#include <fstream>
#include <iostream>
#include <sstream>

#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "token/token.hpp"
#include "codegen/codegen.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // TODO : add support for lex, parse, codegen flags
    if (argc != 2) {
        cerr << "no compilation file provided" << endl;
        exit(1);
    }
    string filename = argv[1];
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();

    cout << endl << "Program:" << endl;
    cout << buffer.str() << endl;
    lexer::Lexer tok(buffer.str());
    vector<token::Token> tokens = tok.Lex();

    cout << endl << "Tokens:" << endl;
    tok.PrintTokens();

    cout << endl << "AST:" << endl;
    parser::ast ast = parser::ast(std::move(tokens));
    auto program_ast = ast.ParseProgram();
    cout << program_ast->toString() << endl;

    cout << endl << "ASM AST:" << endl;
    codegen::ast asm_ast = codegen::ast(std::move(program_ast));
    auto prog_asm_ast = asm_ast.AsmProgram();
    cout <<  prog_asm_ast->toString() << endl;
}