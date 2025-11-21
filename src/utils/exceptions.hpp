#include <string>

class CompilerError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class LexerError : public CompilerError {
public:
    LexerError(const std::string& msg);
};

class ParserError : public CompilerError {
public:
    ParserError(const std::string& msg);
};

class CodegenError : public CompilerError {
public:
    CodegenError(const std::string& msg);
};