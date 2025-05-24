#include "Utils.h"

string join(const vector<string>& vec, const string& separator) {
    string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0 && !result.empty()) result += separator;
        result += vec[i];
    }
    return result;
}

bool is_equivalent(const string& f1, const string& f2) {
    return f1 == f2;
}

vector<char> extract_vars(const string& form) {
    vector<char> vars;
    for (char c : form)
        if (c >= 'a' && c <= 'z')
            if (find(vars.begin(), vars.end(), c) == vars.end())
                vars.push_back(c);
    sort(vars.begin(), vars.end());
    return vars;
}