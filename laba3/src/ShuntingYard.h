#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H

#include <string>

class ShuntingYard {
public:
    std::string postfix;

    ShuntingYard(const std::string& expr);

private:
    std::string convert(const std::string& expr);
    bool isVariable(char c);
    bool isOperator(char op);
    int precedence(char op);
};

#endif // SHUNTINGYARD_H