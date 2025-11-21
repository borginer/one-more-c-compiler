#include "exceptions.hpp"

using namespace std;

LexerError::LexerError(const string& msg) : CompilerError("Lexer: " + msg) {};
ParserError::ParserError(const string& msg)
    : CompilerError("Parser: " + msg) {};
CodegenError::CodegenError(const string& msg)
    : CompilerError("Codegen: " + msg) {};