#include "tokenizer.hpp"
#include "utils.hpp"
#include <cstddef>
#include <optional>
#include <vector>

using namespace std;

Token::Token(string rn, string v) : ruleName(rn), value(v) {}

SymbolNode::SymbolNode(char s, int r) : symbol(s), repeat(r) {}

void SymbolNode::AddChild(SymbolNode *child) { children.push_back(child); }

Tokenizer::Tokenizer() { SymbolTree = new SymbolNode(' ', 0); }

SymbolNode *SymbolNode::childWithSymbol(char c) {
  for (SymbolNode *sym : children) {
    if (sym->symbol == c) {
      return sym;
    }
  }
  return NULL;
}

void SymbolNode::SetRuleName(string ruleName) { this->ruleName = ruleName; }
optional<string> SymbolNode::GetRuleName() { return ruleName; }

void Tokenizer::AddRule(string ruleName, string regex) {
  SymbolNode *p = SymbolTree;
  for (char c : regex) {
    SymbolNode *symChild = p->childWithSymbol(c);
    if (symChild) {
      p = symChild;
    } else {
      SymbolNode *newSym = new SymbolNode(c, 1);
      p->AddChild(newSym);
      p = newSym;
    }
  }
  p->SetRuleName(ruleName);
}

vector<Token *> Tokenizer::Tokenize(string input) {
  vector<string> words = splitString(input);
  SymbolNode *p = SymbolTree;
  vector<Token *> tokens;

  for (string word : words) {
    for (int i = 0; i < word.length(); i++) {
      SymbolNode *symChild = p->childWithSymbol(word[i]);
      if (symChild) {
        if (symChild->GetRuleName().has_value() && i == word.length() - 1) {
          tokens.push_back(new Token(symChild->GetRuleName().value(), word));
        }
        p = symChild;
      } else {
        tokens.push_back(new Token("undef", word));
        break;
      }
    }
    p = SymbolTree;
  }
  return tokens;
}