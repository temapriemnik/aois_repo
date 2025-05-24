#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

string join(const vector<string>& vec, const string& separator = " ∨ ");
bool is_equivalent(const string& f1, const string& f2);
vector<char> extract_vars(const string& form);

#endif // UTILS_H