#ifndef CROSS_REFERENCES_H
#define CROSS_REFERENCES_H

#include <string>

#include "Vector.h"

Vector<std::string> readTextFromConsole();
Vector<std::string> readTextFromFile(const std::string& fileName);
Vector<std::string> getDemoText();

void processText(const Vector<std::string>& lines);
void runTests();

#endif
