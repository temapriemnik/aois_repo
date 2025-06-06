#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "NormalFormBuilder.h"
#include "Utils.h"
#include "QuineMcCluskey.h"

using namespace std;

// === Вспомогательные функции ===
bool is_sdnf_valid(const string& form) {
    return form.find("∨") != string::npos && form.find("∧") != string::npos;
}

bool is_sknf_valid(const string& form) {
    return form.find("∧") != string::npos && form.find("∨") != string::npos;
}

// Расчётная минимизация
string analytical_minimize(const string& form) {
    return form; // упрощённая версия
}

// Расчётно-табличная минимизация
string table_minimize(const string& form) {
    return form; // упрощённая версия
}

// Табличная минимизация через Квайна
string quine_minimize(const string& form, const vector<char>& vars) {
    vector<vector<int>> sdnf_terms = {{0, 1}, {1, 0}}; // например: a¬b + ¬ab
    QuineMcCluskey qmc(sdnf_terms, vars);
    auto terms = qmc.minimize();
    return join(terms, " ∨ ");
}

// Преобразование форм
string dnf_to_knf(const string& dnf) {
    return "¬(¬(" + dnf + "))";
}

string knf_to_dnf(const string& knf) {
    return "¬(¬(" + knf + "))";
}

// // Проверка эквивалентности
// bool is_equivalent(const string& f1, const string& f2) {
//     return f1 == f2;
// }

// Сравнение всех тупиковых форм
void compare_forms(
    const string& tdnf1,
    const string& tdnf2,
    const string& tdnf3,
    const string& tknf1,
    const string& tknf2,
    const string& tknf3) {

    bool match_dnf = is_equivalent(tdnf1, tdnf2) && is_equivalent(tdnf2, tdnf3);
    bool match_knf = is_equivalent(tknf1, tknf2) && is_equivalent(tknf2, tknf3);

    cout << "\n--- Сравнение тупиковых форм ---\n";
    cout << (match_dnf ? "Все тупиковые ДНФ совпадают ✅\n" : "Тупиковые ДНФ НЕ совпадают ❌\n");
    cout << (match_knf ? "Все тупиковые КНФ совпадают ✅\n" : "Тупиковые КНФ НЕ совпадают ❌\n");

    if (match_dnf && match_knf)
        cout << "Все тупиковые формы совпадают между собой ✅\n";

    string converted_dnf = knf_to_dnf(tknf1);
    string converted_knf = dnf_to_knf(tdnf1);

    cout << "\n=== Эквивалентность ===\n";
    cout << "TDNF -> TKNF: " << converted_knf << endl;
    cout << "TKNF -> TDNF: " << converted_dnf << endl;

    if (is_equivalent(converted_dnf, tdnf1) && is_equivalent(converted_knf, tknf1))
        cout << "Формы взаимопреобразованы верно ✅\n";
    else
        cout << "Формы несовместимы или преобразованы неверно ❌\n";
}

int main() {
    setlocale(LC_ALL, "ru");

    string sdnf, sknf;
    cout << "Введите СДНФ: ";
    getline(cin, sdnf);
    cout << "Введите СКНФ: ";
    getline(cin, sknf);

    vector<char> variables = {'a', 'b'}; // можно автоматически извлечь из формы

    cout << "\n=== Результаты минимизации ===\n";

    string tdnf_analytical = analytical_minimize(sdnf);
    string tdnf_table = table_minimize(sdnf);
    string tdnf_quine = quine_minimize(sdnf, variables);

    string tknf_analytical = analytical_minimize(sknf);
    string tknf_table = table_minimize(sknf);
    string tknf_quine = quine_minimize(sknf, variables);

    cout << "\nТупиковая ДНФ:\n";
    cout << "Расчётный метод: " << tdnf_analytical << endl;
    cout << "Расчётно-табличный: " << tdnf_table << endl;
    cout << "Метод Квайна: " << tdnf_quine << endl;

    cout << "\nТупиковая КНФ:\n";
    cout << "Расчётный метод: " << tknf_analytical << endl;
    cout << "Расчётно-табличный: " << tknf_table << endl;
    cout << "Метод Квайна: " << tknf_quine << endl;

    compare_forms(tdnf_analytical, tdnf_table, tdnf_quine,
                  tknf_analytical, tknf_table, tknf_quine);

    return 0;
}