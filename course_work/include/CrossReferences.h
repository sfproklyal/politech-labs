#ifndef CROSS_REFERENCES_H
#define CROSS_REFERENCES_H

#include <string>
#include <vector>

std::vector<std::string> readTextFromFile(const std::string& path);
std::vector<std::string> readTextFromConsole();
std::vector<std::string> getDemoText();

void processText(const std::vector<std::string>& lines);
void runTests();

#endif
