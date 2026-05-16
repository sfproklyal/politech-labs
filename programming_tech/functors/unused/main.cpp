#include <iostream>
#include <vector>
#include <algorithm>

struct Object {
    int a;
    int b;
};

struct isCorrect {
    bool operator()(const Object& obj) {
        return (obj.a > obj.b) && (obj.a + obj.b > 10);
    }
};


int main() {

    std::vector<Object> objects{
        {1, 5},
        {10, 3},
        {4, 4},
        {8, 2},
        {6, 9}
    };

    int count = count_if(
        objects.begin(),
        objects.end(),
        isCorrect()
    );

    std::cout << count << '\n';
    int limit = 10;

    int countLambda = count_if(
        objects.begin(),
        objects.end(),
        [limit](const Object& obj) {
            return (obj.a > obj.b) && (obj.a + obj.b > 10) && (obj.a + obj.b > limit);
        }
    );

    std::cout << countLambda << '\n';


    return 0;
};


// struct greaterThan8 {
//     bool operator()(int x) {
//         return x > 8;
//     }
// };

// int main(){
//     std::vector<int> numbers{1, 4, 7, 10, 13, 16};

//     int count = std::count_if (
//         numbers.begin(),
//         numbers.end(),
//         greaterThan8()
//     );

//     std::cout << count << '\n';


//     int countLambda = std::count_if (
//         numbers.begin(),
//         numbers.end(),
//         [](int x) {
//             return x > 9;
//         }
//     );

//     std::cout << countLambda << '\n';

    
// }
