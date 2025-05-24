#include "ShuntingYard.h"
#include <vector>
#include <string>

ShuntingYard::ShuntingYard(const std::string& expr) {
    postfix = convert(expr);
}

std::string ShuntingYard::convert(const std::string& expr) {
    std::string output;
    std::vector<char> stack;

    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];

        if (isVariable(c)) {
            output += c;
        } else if (c == '(') {
            stack.push_back(c);
        } else if (c == ')') {
            while (!stack.empty() && stack.back() != '(') {
                output += stack.back();
                stack.pop_back();
            }
            stack.pop_back();
        } else if (c == '!') {
            stack.push_back(c);
        } else if (isOperator(c)) {
            while (!stack.empty() && precedence(stack.back()) >= precedence(c)) {
                output += stack.back();
                stack.pop_back();
            }
            stack.push_back(c);
        }
    }

    while (!stack.empty()) {
        output += stack.back();
        stack.pop_back();
    }

    return output;
}

bool ShuntingYard::isVariable(char c) {
    return c >= 'a' && c <= 'z';
}

bool ShuntingYard::isOperator(char op) {
    return std::string("&|>=").find(op) != std::string::npos;
}

int ShuntingYard::precedence(char op) {
    if (op == '!') return 4;
    if (op == '&') return 3;
    if (op == '|') return 2;
    if (op == '>') return 1;
    if (op == '=') return 1;
    return 0;
}