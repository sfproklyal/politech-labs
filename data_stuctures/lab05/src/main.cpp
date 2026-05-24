#include <iostream>
#include "HashTable.h"
#include <string>

int main(){
    try {
        HashTable table(-5);
        table.insert(13.3, "ads");
        table.insert(15.3, "adsds");
        table.insert(34.2, "newnew");
        table.insert(32.32, "newnewew");
        table.print();

        std::cout << std::string(20, '-') << '\n';
        table.remove(13.3);
        table.print();

        std::cout << std::string(20, '-') << '\n';
        table.insert(13.3, "a");
        table.insert(18.5, "b");
        table.insert(23.0, "c");
        table.print();        

        std::string value;
        if (table.find(15.3, value)) {
            std::cout << "Find method is working! Value: " << value << '\n'; 
        }

        std::cout << "Longest chain: " << table.longestChain() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }


}
