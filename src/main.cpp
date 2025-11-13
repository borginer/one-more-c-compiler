#include "tokenizer.hpp"
#include "utils.hpp"
#include <iostream>

using namespace std;

int main() {
  Tokenizer tok;
  tok.AddRule("myName", "ariel");
  tok.AddRule("is", "is");
  tok.AddRule("learning", "learning");
  vector<Token *> tokens = tok.Tokenize("ariel is learning unexpected");
  for (Token *t : tokens) {
    cout << t->ruleName << " | " << t->value << endl;
  }
}