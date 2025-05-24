#include "Evaluator.h"
#include <vector>

Evaluator::Evaluator(const std::string& postfixExpr) : postfix(postfixExpr) {}

int Evaluator::evaluate() {
    std::vector<int> stack;

    for (char token : postfix) {
        if (token >= 'a' && token <= 'z') {
            stack.push_back(values[token]);
        } else if (token == '!') {
            int a = stack.back(); stack.pop_back();
            stack.push_back(1 - a);
        } else {
            int b = stack.back(); stack.pop_back();
            int a = stack.back(); stack.pop_back();

            if (token == '&') stack.push_back(a & b);
            else if (token == '|') stack.push_back(a | b);
            else if (token == '>') stack.push_back((a == 1 && b == 0) ? 0 : 1);
            else if (token == '=') stack.push_back((a == b) ? 1 : 0);
        }
    }

    return stack.back();
}