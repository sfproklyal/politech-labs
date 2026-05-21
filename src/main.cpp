#include <iostream>
#include <stdexcept>
#include <string>

#include "CrossReferences.h"

int main()
{
    try {
        std::cout << "1 - enter text\n";
        std::cout << "2 - read text from file\n";
        std::cout << "3 - demo text\n";
        std::cout << "4 - run tests\n";
        std::cout << "Choice: ";

        int choice = 0;
        std::cin >> choice;
        std::cin.ignore(10000, '\n');

        if (choice == 1) {
            processText(readTextFromConsole());
        }
        else if (choice == 2) {
            std::string path;
            std::cout << "File path: ";
            std::getline(std::cin, path);
            processText(readTextFromFile(path));
        }
        else if (choice == 3) {
            processText(getDemoText());
        }
        else if (choice == 4) {
            runTests();
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
