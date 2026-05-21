#ifndef CROSS_REFERENCES_H
#define CROSS_REFERENCES_H

#include <string>
#include <vector>

#include "RedBlackTree.h"

std::string toLower(const std::string& word);
bool isWordSymbol(unsigned char ch);

void addLineToTree(RedBlackTree& tree,
                   const std::string& line,
                   int lineNumber);
void buildCrossReferences(const std::vector<std::string>& lines,
                          RedBlackTree& tree);

std::vector<std::string> readTextFromFile(const std::string& path);
std::vector<std::string> readTextFromConsole();
std::vector<std::string> getDemoText();

void printNumberedText(const std::vector<std::string>& lines);
void printCrossReferences(const RedBlackTree& tree);
void processText(const std::vector<std::string>& lines);
void runTests();

#endif
