#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

// [](int a, int b){ return a > b || a == b * 2; }

int main() {
    using namespace std::placeholders;

    auto f = std::bind(
        std::logical_or<bool>(),
        std::bind(std::greater<int>(), _1, _2),
        std::bind(
            std::equal_to<int>(),
            _1,
            std::bind(std::multiplies<int>(), _2, 2)
        )
    );

    std::cout << std::boolalpha << f(4, 2) << '\n';

    return 0;
}




//[](int a, int b){ return a % 10 == a - b; }


// int main() {
//     using namespace std::placeholders;

//     auto f = std::bind(
//         std::equal_to<int>(),
//         std::bind(std::modulus(), _1, 10),
//         std::bind(std::minus(), _1, _2)
//     );/

    

//     return 0;
// }




// struct Num {
//     int a;
//     int b;
// };


// int main() {
//     std::vector<int> numbers {1, 2, 4, 5, 6};

//     using namespace std::placeholders;

//     auto greaterThan4 = std::bind(std::greater<int>(), _1, 4);

//     int count = std::count_if(
//         numbers.begin(),
//         numbers.end(),
//         greaterThan4
//     );

//     std::cout << count << '\n';

// };
