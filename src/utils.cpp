#include "utils.hpp"
#include <vector>

using namespace std;

vector<string> splitString(string input) {
  vector<string> tokens;
  int i = 0;
  int prev = 0;
  while (i < input.length()) {
    if (input[i] == ' ') {
      tokens.push_back(input.substr(prev, i - prev));
      while (input[i] == ' ') {
        i++;
      }
      prev = i;
    } else {
        i++;
    }
  }
  
  if (i > prev) {
    tokens.push_back(input.substr(prev, i - prev));
  }

  return tokens;
}