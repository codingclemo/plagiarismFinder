#pragma once

#include <string>
#include <fstream>

bool isPunct(char ch);
bool isDigit(char ch);
bool isAlpha(char ch);

char toLower(char ch);

std::string normalize(std::string word);
void openStream(int argc, char *argv[], std::ifstream &fin, int argNumber);