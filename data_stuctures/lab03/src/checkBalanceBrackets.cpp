#include <cstddef>
#include "StackArray.h"
#include "Exceptions.h"

bool checkBalanceBrackets(const char* text, const int maxDeep) {
    if (text == nullptr || maxDeep <= 0) throw std::invalid_argument("Text ");

    try {
        StackArray<char> st(static_cast<size_t>(maxDeep));

        for (size_t i = 0; text[i] != '\0'; i++) {
            char c = text[i];

            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            }
            else if (c == ')' || c == ']' || c == '}') {
                if (st.isEmpty()) return false;

                char br = st.pop();

                if ((c == ')' && br != '(') ||
                    (c == ']' && br != '[') ||
                    (c == '}' && br != '{')) {
                    return false;
                }
            }
        }

        return st.isEmpty();
    }

    catch (const StackOverflow&) {
        return false;
    }

    catch (const StackUnderflow&) {
        return false;
    }
}