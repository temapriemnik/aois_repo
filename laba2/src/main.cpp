#include <iostream>
#include "Lexer.h"
#include "ShuntingYard.h"
#include "TruthTableGenerator.h"
#include "NormalFormBuilder.h"

int main() {
    setlocale(LC_ALL, "ru");

    std::cout << "Введите логическое выражение: ";
    std::string expr;
    std::getline(std::cin, expr);

    Lexer lexer(expr);
    ShuntingYard shuntingYard(lexer.expr);

    std::cout << "\nПостфиксная форма: " << shuntingYard.postfix << std::endl;

    TruthTableGenerator truthTable(lexer.variables, shuntingYard.postfix);
    NormalFormBuilder forms(lexer.variables, truthTable.table);

    std::cout << "\nТаблица истинности:\n";
    for (char var : lexer.variables) std::cout << var << " | ";
    std::cout << "Результат\n";

    for (const auto& row : truthTable.table) {
        for (int val : row.combo) std::cout << val << " | ";
        std::cout << row.result << std::endl;
    }

    std::cout << "\nСДНФ:\n" << forms.sdnf << std::endl;
    std::cout << "Числовая форма СДНФ: ∨(" << forms.numeric_sdnf << ")\n";

    std::cout << "\nСКНФ:\n" << forms.sknf << std::endl;
    std::cout << "Числовая форма СКНФ: ∧(" << forms.numeric_sknf << ")\n";

    std::cout << "\nИндексная форма:\n" << forms.index_form << std::endl;

    return 0;
}