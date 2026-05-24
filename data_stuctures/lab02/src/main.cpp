#include "DoubleOrderedDuplicateList.h"
#include <cassert>
#include <iostream>

int main() {
    DoubleOrderedDuplicateList<int> list;
    assert(list.isEmpty());
    assert(list.size() == 0);

    list.insert(5);
    list.insert(1);
    list.insert(3);
    list.insert(3);
    list.insert(2);
    
    assert(list.size() == 5);
    assert(list.head() == 1);
    assert(list.tail() == 5);

    assert(list.search(1));
    assert(list.search(2));
 
    DoubleOrderedDuplicateList<int> list2;
    list2 += 4;
    list2 += 1;
    list2 += 4;

    DoubleOrderedDuplicateList<int> list3;
    list3.insert(2);
    list3.insert(1);
    list3.insert(3);

    list3.removeHead();

    assert(list3.size() == 2);
    assert(list3.head() == 2);
    assert(list3.tail() == 3);


    DoubleOrderedDuplicateList<int> list4;
    list4.insert(10);
    list4.insert(20);

    list4.clear();

    assert(list4.isEmpty());
    assert(list4.size() == 0);

    DoubleOrderedDuplicateList<int> a;
    a.insert(1);
    a.insert(2);

    DoubleOrderedDuplicateList<int> b;
    b = a;


    DoubleOrderedDuplicateList<int> list5;
    list5.insert(1);
    list5.insert(3);
    list5.insert(5);
    list5.insert(6);
    list5.insert(7);

    list5.removeKey(3, 6);
    list5.print();
    std::cout << '\n';

    DoubleOrderedDuplicateList<int> list6;
    list6.insert(1);
    list6.insert(2);
    list6.insert(2);
    list6.insert(5);

    list6.replace(2, 4);
    list6.print();
    std::cout << '\n';

    list6.printBack();
    std::cout << '\n';


    DoubleOrderedDuplicateList<int> m1;
    m1.insert(1);
    m1.insert(3);
    m1.insert(5);

    DoubleOrderedDuplicateList<int> m2;
    m2.insert(2);
    m2.insert(3);
    m2.insert(4);

    m1.merge(m2);

    assert(m2.isEmpty());
    assert(m2.size() == 0);

    std::cout << "tests ok\n";
    return 0;
}