#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <map>
#include <string>

class Evaluator {
public:
    std::map<char, int> values;
    std::string postfix;

    Evaluator(const std::string& postfixExpr);

    int evaluate();
};

#endif // EVALUATOR_H