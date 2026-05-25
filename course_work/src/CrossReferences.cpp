#include "CrossReferences.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "RedBlackTree.h"

namespace {

std::string toLower(const std::string& word)
{
    std::string result = word;
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = static_cast<char>(result[i] - 'A' + 'a');
        }
    }
    return result;
}

bool isWordSymbol(unsigned char ch)
{
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
           (ch >= '0' && ch <= '9');
}

std::string lineListToString(const LineList* lines)
{
    if (lines == nullptr) {
        return "";
    }

    return lines->toString();
}

std::string treeToString(const RedBlackTree& tree)
{
    return tree.toString();
}

void check(bool condition,
           const std::string& testName,
           int& passed,
           int& failed)
{
    if (condition) {
        std::cout << "[PASS] " << testName << '\n';
        passed++;
    }
    else {
        std::cout << "[FAIL] " << testName << '\n';
        failed++;
    }
}

void addLineToTree(RedBlackTree& tree,
                   const std::string& line,
                   int lineNumber)
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

void buildCrossReferences(const Vector<std::string>& lines,
                          RedBlackTree& tree)
{
    for (size_t i = 0; i < lines.size(); i++) {
        addLineToTree(tree, lines[i], static_cast<int>(i + 1));
    }
}

void printNumberedText(const Vector<std::string>& lines)
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

bool throwsInvalidArgumentForEmptyKey()
{
    RedBlackTree tree;
    try {
        tree.insert("", 1);
    }
    catch (const std::invalid_argument&) {
        return true;
    }
    return false;
}

bool throwsInvalidArgumentForBadLine()
{
    RedBlackTree tree;
    try {
        tree.insert("word", 0);
    }
    catch (const std::invalid_argument&) {
        return true;
    }
    return false;
}

bool throwsInvalidArgumentForLineList()
{
    LineList lines;
    try {
        lines.insert(0);
    }
    catch (const std::invalid_argument&) {
        return true;
    }
    return false;
}

bool throwsRuntimeErrorForMissingFile()
{
    try {
        readTextFromFile("__missing_course_work_input__.txt");
    }
    catch (const std::runtime_error&) {
        return true;
    }
    return false;
}

}  // namespace

Vector<std::string> readTextFromFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Can not open file: " + path);
    }

    Vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

Vector<std::string> readTextFromConsole()
{
    Vector<std::string> lines;
    std::string line;

    std::cout << "Enter text. Empty line finishes input.\n";
    while (std::getline(std::cin, line) && !line.empty()) {
        lines.push_back(line);
    }

    return lines;
}

Vector<std::string> getDemoText()
{
    Vector<std::string> lines;
    lines.push_back("Apple is red.");
    lines.push_back("Tree is green.");
    lines.push_back("Apple grows on tree.");
    return lines;
}

void processText(const Vector<std::string>& lines)
{
    RedBlackTree tree;
    buildCrossReferences(lines, tree);

    printNumberedText(lines);
    printCrossReferences(tree);
}

void runTests()
{
    int passed = 0;
    int failed = 0;

    {
        RedBlackTree tree;
        tree.insert("tree", 1);
        check(lineListToString(tree.search("tree")) == "1" && tree.isValid(),
              "insert one word",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("tree", 1);
        tree.insert("tree", 1);
        check(lineListToString(tree.search("tree")) == "1" && tree.isValid(),
              "duplicate line number is not stored",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("tree", 1);
        tree.insert("tree", 3);
        check(lineListToString(tree.search("tree")) == "1, 3" &&
                  tree.isValid(),
              "same word in different lines",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("tree", 1);
        check(tree.search("tree") != nullptr && tree.isValid(),
              "search existing word",
              passed,
              failed);
        check(tree.search("missing") == nullptr && tree.isValid(),
              "search missing word",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("tree", 1);
        check(tree.remove("tree") && tree.search("tree") == nullptr &&
                  tree.isValid(),
              "remove existing word",
              passed,
              failed);
        check(!tree.remove("missing") && tree.isValid(),
              "remove missing word",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("b", 1);
        tree.insert("a", 1);
        tree.insert("c", 1);
        check(tree.remove("b") && tree.isValid(),
              "remove root",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("d", 1);
        tree.insert("b", 1);
        tree.insert("f", 1);
        tree.insert("a", 1);
        tree.insert("c", 1);
        tree.insert("e", 1);
        tree.insert("g", 1);
        check(tree.remove("a") && tree.isValid(),
              "remove leaf",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("b", 1);
        tree.insert("a", 1);
        tree.insert("c", 1);
        tree.insert("d", 1);
        check(tree.remove("c") && tree.isValid(),
              "remove node with one child",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("d", 1);
        tree.insert("b", 1);
        tree.insert("f", 1);
        tree.insert("a", 1);
        tree.insert("c", 1);
        tree.insert("e", 1);
        tree.insert("g", 1);
        check(tree.remove("d") && tree.isValid(),
              "remove node with two children",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("apple", 1);
        tree.insert("banana", 1);
        tree.insert("cat", 1);
        tree.insert("dog", 1);
        tree.insert("elephant", 1);
        check(treeToString(tree) ==
                  "apple : 1\nbanana : 1\ncat : 1\n"
                  "dog : 1\nelephant : 1\n" &&
                  tree.isValid(),
              "alphabetical insertion keeps tree valid",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        tree.insert("elephant", 1);
        tree.insert("dog", 1);
        tree.insert("cat", 1);
        tree.insert("banana", 1);
        tree.insert("apple", 1);
        check(treeToString(tree) ==
                  "apple : 1\nbanana : 1\ncat : 1\n"
                  "dog : 1\nelephant : 1\n" &&
                  tree.isValid(),
              "reverse insertion keeps tree valid",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        Vector<std::string> lines;
        lines.push_back("Apple, apple! Tree.");
        buildCrossReferences(lines, tree);
        check(treeToString(tree) == "apple : 1\ntree : 1\n" &&
                  tree.isValid(),
              "punctuation separates words",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        Vector<std::string> lines;
        lines.push_back("Tree tree TREE");
        buildCrossReferences(lines, tree);
        check(treeToString(tree) == "tree : 1\n" && tree.isValid(),
              "latin case is ignored",
              passed,
              failed);
    }

    {
        RedBlackTree tree;
        Vector<std::string> lines;
        buildCrossReferences(lines, tree);
        check(tree.isEmpty() && tree.isValid(),
              "empty text",
              passed,
              failed);
    }

    check(throwsRuntimeErrorForMissingFile(),
          "missing file throws exception",
          passed,
          failed);
    check(throwsInvalidArgumentForEmptyKey(),
          "empty key throws exception",
          passed,
          failed);
    check(throwsInvalidArgumentForBadLine(),
          "bad tree line number throws exception",
          passed,
          failed);
    check(throwsInvalidArgumentForLineList(),
          "bad list line number throws exception",
          passed,
          failed);

    std::cout << "\nTests passed: " << passed << '\n';
    std::cout << "Tests failed: " << failed << '\n';
}
