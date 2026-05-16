#include <iostream>
#include <functional>
#include <iterator>
#include <vector>

struct Object {
    int a;
    int b;
};

std::ostream& operator<<(std::ostream& out, const Object& obj) {
    return out << '(' << obj.a << ',' << obj.b << ')';
};

int main() {

    std::vector<Object> vec = {
        {1, 2},
        {2, 3},
        {4, 5}
    };

    std::copy(
        vec.begin(), 
        vec.end(), 
        std::ostream_iterator<Object>(std::cout, " ")
    );
    
};