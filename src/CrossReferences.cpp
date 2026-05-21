#include "CrossReferences.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>

std::string toLower(const std::string& word)
{
    std::string result = word;
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(result[i])));
    }
    return result;
}

bool isWordSymbol(unsigned char ch)
{
    return std::isalnum(ch) || ch >= 128;
}

void addLineToTree(RedBlackTree& tree, const std::string& line, int lineNumber)
{
    std::string word;

    for (size_t i = 0; i <= line.size(); i++) {
        unsigned char ch = 0;
        if (i < line.size()) {
            ch = static_cast<unsigned char>(line[i]);
        }

        if (i < line.size() && isWordSymbol(ch)) {
            word += static_cast<char>(ch);
        }
        else if (!word.empty()) {
            tree.insert(toLower(word), lineNumber);
            word.clear();
        }
    }
}

void buildCrossReferences(const std::vector<std::string>& lines,
                          RedBlackTree& tree)
{
    for (size_t i = 0; i < lines.size(); i++) {
        addLineToTree(tree, lines[i], static_cast<int>(i + 1));
    }
}

std::vector<std::string> readTextFromFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Can not open file");
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> readTextFromConsole()
{
    std::vector<std::string> lines;
    std::string line;

    std::cout << "Enter text. Empty line finishes input.\n";
    while (std::getline(std::cin, line) && !line.empty()) {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> getDemoText()
{
    return {
        "Red black tree stores words.",
        "Tree keeps words sorted.",
        "Words can repeat, but line numbers are stored once."
    };
}

void printNumberedText(const std::vector<std::string>& lines)
{
    std::cout << "\nText with line numbers:\n";
    for (size_t i = 0; i < lines.size(); i++) {
        std::cout << i + 1 << ": " << lines[i] << '\n';
    }
}

void printCrossReferences(const RedBlackTree& tree)
{
    std::cout << "\nCross references:\n";
    if (tree.isEmpty()) {
        std::cout << "Table is empty\n";
    }
    else {
        tree.print(std::cout);
    }
}

void processText(const std::vector<std::string>& lines)
{
    RedBlackTree tree;
    buildCrossReferences(lines, tree);

    printNumberedText(lines);
    printCrossReferences(tree);
}

void runTests()
{
    RedBlackTree tree;
    tree.insert("tree", 1);
    tree.insert("tree", 1);
    tree.insert("tree", 3);
    tree.insert("algorithm", 2);
    tree.insert("data", 2);

    std::cout << "\nTest search existing word: ";
    const LineList* lines = tree.search("tree");
    if (lines != nullptr) {
        lines->print(std::cout);
    }
    else {
        std::cout << "not found";
    }

    std::cout << "\nTest search missing word: ";
    std::cout << (tree.search("missing") == nullptr ? "not found" : "found");

    std::cout << "\nTest remove word: ";
    std::cout << (tree.remove("data") ? "removed" : "not removed");

    std::cout << "\nTree after tests:\n";
    tree.print(std::cout);

    std::cout << "\nTest invalid empty key: ";
    try {
        tree.insert("", 1);
        std::cout << "not detected";
    }
    catch (const std::invalid_argument&) {
        std::cout << "detected";
    }

    std::cout << "\nTest invalid line number: ";
    try {
        tree.insert("word", 0);
        std::cout << "not detected";
    }
    catch (const std::invalid_argument&) {
        std::cout << "detected";
    }
}
