#include <iostream>
#include <functional>

int add(int a, int b) {
    return a + b;
}

int main() {
    // [] (int a, int b) {
    //     return (a + b) * (a - b);
    // };

    using namespace std::placeholders;

    auto add10(int a) = std::bind(add, 10, a);

    std::cout << add(2, 3) << '\n';

    
}

