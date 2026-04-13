#include "StackArray.h"
#include <iostream>

int main() {
    StackArray<int> a(10);
    std::cout << a.isEmpty() << '\n';
    a.push(10);
    a.push(22);
    std::cout << a.pop() << '\n';
    std::cout << a.pop() << '\n';
    std::cout << a.isEmpty() << '\n';
}
