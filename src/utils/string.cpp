#include "utils/string.hpp"

using namespace std;

string util::repeatTabs(size_t n) {
    string tab = "    ";
    string ret;
    ret.reserve(n * tab.size());

    for (size_t i = 0; i < n; i++) {
        ret += tab;
    }

    return ret;
}