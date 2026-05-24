#include <iostream>
#include "Vector.h"

int main() {
    Vector<int> a;
    Vector<int> b;
    Vector<int> c(3);
    Vector<int> d(4, 7);

    std::cout << "a size = " << a.size() << "\n";
    std::cout << "c size = " << c.size() << "\n";
    std::cout << "d size = " << d.size() << "\n";
    std::cout << "d[0] = " << d[0] << "\n";
    std::cout << "d[1] = " << d[1] << "\n";

    if (a == b) {
        std::cout << "a == b\n";
    }

    a.push_back(10);
    a.push_back(20);
    a.push_back(30);

    std::cout << "after push_back\n";
    std::cout << a[0] << "\n";
    std::cout << a[1] << "\n";
    std::cout << a[2] << "\n";

    std::cout << "front = " << a.front() << "\n";
    std::cout << "back = " << a.back() << "\n";
    std::cout << "at(1) = " << a.at(1) << "\n";

    a.insert(1, 99);

    std::cout << "after insert\n";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    a.erase(2);

    std::cout << "after erase index\n";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    a.push_back(100);
    a.push_back(200);
    a.push_back(300);

    std::cout << "before erase range\n";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    a.erase(1, 3);

    std::cout << "after erase range\n";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    a.resize(6);

    std::cout << "after resize(6)\n";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    a.resize(8, 5);

    std::cout << "after resize(8, 5)\n";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    a.pop_back();

    std::cout << "after pop_back\n";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    b.push_back(111);
    b.push_back(222);

    std::cout << "before swap\n";
    std::cout << "a: ";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    std::cout << "b: ";
    for (size_t i = 0; i < b.size(); i++) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n";

    a.swap(b);

    std::cout << "after swap\n";
    std::cout << "a: ";
    for (size_t i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";

    std::cout << "b: ";
    for (size_t i = 0; i < b.size(); i++) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n";

    Vector<int> e(a);
    std::cout << "copy constructor\n";
    for (size_t i = 0; i < e.size(); i++) {
        std::cout << e[i] << " ";
    }
    std::cout << "\n";

    Vector<int> f;
    f = a;
    std::cout << "copy assignment\n";
    for (size_t i = 0; i < f.size(); i++) {
        std::cout << f[i] << " ";
    }
    std::cout << "\n";

    Vector<int> g(std::move(a));
    std::cout << "move constructor\n";
    for (size_t i = 0; i < g.size(); i++) {
        std::cout << g[i] << " ";
    }
    std::cout << "\n";

    Vector<int> h;
    h = std::move(b);
    std::cout << "move assignment\n";
    for (size_t i = 0; i < h.size(); i++) {
        std::cout << h[i] << " ";
    }
    std::cout << "\n";

    g.clear();
    std::cout << "g size after clear = " << g.size() << "\n";

    if (g.empty()) {
        std::cout << "g is empty\n";
    }

    try {
        std::cout << g.at(0) << "\n";
    }
    catch (const std::out_of_range& e) {
        std::cout << "exception caught\n";
    }

    return 0;
}


