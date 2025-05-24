#include "Lexer.h"
#include <algorithm>

Lexer::Lexer(const std::string& input) {
    expr = preprocess(input);
    extractVariables();
}

std::string Lexer::preprocess(const std::string& s) {
    std::string result = s;
    replaceAll(result, "∨", "|");
    replaceAll(result, "∧", "&");
    replaceAll(result, "→", ">");
    replaceAll(result, "->", ">");
    replaceAll(result, "∼", "=");
    replaceAll(result, "~", "=");
    replaceAll(result, "¬", "!");
    return result;
}

void Lexer::extractVariables() {
    for (char c : expr)
        if (c >= 'a' && c <= 'e')
            if (std::find(variables.begin(), variables.end(), c) == variables.end())
                variables.push_back(c);
    std::sort(variables.begin(), variables.end());
}

void Lexer::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
}