#include "register.hpp"

using namespace std;
using namespace reg;

string reg::toString(Type type) {
    switch (type) {
        case EAX:
            return "eax";
    }
}