#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

class Lexer {
public:
    std::string expr;
    std::vector<char> variables;

    Lexer(const std::string& input);

    static void replaceAll(std::string& str, const std::string& from, const std::string& to);

private:
    std::string preprocess(const std::string& s);
    void extractVariables();
};

#endif // LEXER_H