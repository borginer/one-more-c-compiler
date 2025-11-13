#include <optional>
#include <string>
#include <vector>

class Token {
  public:
  std::string ruleName;
  std::string value;
  Token(std::string ruleName, std::string val);
};

class SymbolNode {
    char symbol;
    int repeat;
    std::optional<std::string> ruleName;
    std::vector<SymbolNode*> children;

    public:
    SymbolNode* childWithSymbol(char c);
    SymbolNode(char symbol, int repeat);
    void AddChild(SymbolNode* child);
    void SetRuleName(std::string ruleName);
    std::optional<std::string> GetRuleName();
};

class Tokenizer {
  SymbolNode* SymbolTree;

  public:
  Tokenizer();
  void AddRule(std::string name, std::string regex);
  std::vector<Token*> Tokenize(std::string input);
};

