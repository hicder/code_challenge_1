#include <iostream>
#include <sstream>
#include <string>

#include "util.h"

using namespace std;

namespace {

string getInput() {
  stringstream input;
  string line;
  // Read until EOF
  while (getline(cin, line)) {
    input << line;
  }
  return input.str();
}

} // namespace

int main() {
  string input = getInput();
  cout << mongo::flattenJson(std::move(input)) << endl;
  return 0;
}
