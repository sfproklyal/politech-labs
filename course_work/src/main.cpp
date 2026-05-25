#include <iostream>
#include <stdexcept>
#include <string>

#include "CrossReferences.h"

int main()
{
    try {
        std::cout << "1 - enter text\n";
        std::cout << "2 - demo text\n";
        std::cout << "3 - run tests\n";
        std::cout << "4 - read text from file\n";
        std::cout << "Choice: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cout << "Wrong choice\n";
            return 0;
        }
        std::cin.ignore(10000, '\n');

        if (choice == 1) {
            processText(readTextFromConsole());
        }
        else if (choice == 2) {
            processText(getDemoText());
        }
        else if (choice == 3) {
            runTests();
        }
        else if (choice == 4) {
            std::string fileName;
            std::cout << "Enter file name: ";
            std::getline(std::cin, fileName);
            processText(readTextFromFile(fileName));
        }
        else {
            std::cout << "Wrong choice\n";
        }
    }
    catch (const std::exception& exception) {
        std::cout << "Error: " << exception.what() << '\n';
    }

    return 0;
}
