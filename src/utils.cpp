#include "utils.h"

#include <cstdlib>
#include <string>
#include <ostream>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

bool isPunct(char ch) { return static_cast<bool>(ispunct(ch)); }
bool isDigit(char ch) { return static_cast<bool>(isdigit(ch)); }
bool isAlpha(char ch) { return static_cast<bool>(isalpha(ch)); }

char toLower(char ch) { return static_cast<char>(tolower(ch)); }

string normalize(string word) {
  string::iterator newEnd;
  // e.g. 'H3ll?o'
  newEnd = remove_if(word.begin(), word.end(), isPunct); // copies non-punct forward
  // -> 'H3llo <newEnd> o'
  newEnd = remove_if(word.begin(), newEnd, isDigit); // moves non-digits forward
  // -> 'Hllo <newEnd> oo'
  word.erase(newEnd, word.end()); // actually removes elements
  // -> 'Hllo'
  transform(word.begin(), word.end(), word.begin(), toLower);
  // -> 'hllo'
  return word;
}


// adapt openStream to be able to open two files
void openStream(int argc, char *argv[], ifstream &fin, int argNumber) {
  if (argc < 2 || argc < argNumber) {
    cerr << "usage: " << argv[0] << " file name file name" << endl;
    exit(1);
  }
  // ifstream fin(argv[0]); // ERROR: automatic variable, file closed on return
  fin.open(argv[argNumber]);
  if (fin.fail()) {
    cerr << "file " << argv[argNumber] << " not found" << endl;
    exit(2);
  }
  // fin returned in reference argument
}