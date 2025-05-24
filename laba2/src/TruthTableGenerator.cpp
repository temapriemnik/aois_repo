#include "TruthTableGenerator.h"
#include "Evaluator.h"
#include <cmath>

TruthTableGenerator::TruthTableGenerator(const std::vector<char>& vars, const std::string& pf)
    : variables(vars), postfix(pf) {
    int n = variables.size();
    for (int i = 0; i < pow(2, n); ++i) {
        std::vector<int> combo;
        for (int j = 0; j < n; ++j)
            combo.push_back((i >> (n - 1 - j)) & 1);

        Evaluator eval(postfix);
        for (int k = 0; k < n; ++k)
            eval.values[variables[k]] = combo[k];

        int res = eval.evaluate();
        table.push_back({combo, res});
    }
}

// Генерация всех возможных комбинаций и вычисление результата
void TruthTableGenerator::generate() {
    int n = variables.size();
    for (int i = 0; i < pow(2, n); ++i) {
        std::vector<int> combo;
        for (int j = 0; j < n; ++j)
            combo.push_back((i >> (n - 1 - j)) & 1);  // Генерация битовой комбинации

        Evaluator eval(postfix);
        for (int k = 0; k < n; ++k)
            eval.values[variables[k]] = combo[k];  // Присваиваем значения переменным

        int res = eval.evaluate();
        table.push_back({combo, res});  // Сохраняем результат
    }
}