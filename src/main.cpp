#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include "codegen/codegen.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "token/token.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    // TODO : add support for lex, parse, codegen flags
    if (argc != 2) {
        cerr << "no compilation file provided" << endl;
        return -1;
    }
    try {
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
        auto program_ast = ast.Parse();
        cout << program_ast->toString() << endl;

        cout << endl << "ASM AST:" << endl;
        codegen::asm_ast aa = codegen::asm_ast(std::move(program_ast));
        auto prog_asm_ast = aa.Parse();
        cout << prog_asm_ast->toString() << endl;

        codegen::EmitAsm(filename + ".s", std::move(prog_asm_ast));

    } catch (const std::exception& e) {
        cerr << e.what() << "\n";
        return -1;
    }
}