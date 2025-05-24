#ifndef TRUTHTABLEGENERATOR_H
#define TRUTHTABLEGENERATOR_H

#include <vector>
#include <string>
#include <map>

struct Row {
    std::vector<int> combo;
    int result;
};

class TruthTableGenerator {
public:
    std::vector<Row> table;
    std::vector<char> variables;
    std::string postfix;

    TruthTableGenerator(const std::vector<char>& vars, const std::string& pf);

    void generate();
};

#endif // TRUTHTABLEGENERATOR_H