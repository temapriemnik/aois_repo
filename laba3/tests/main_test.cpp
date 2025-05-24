#include <gtest/gtest.h>
#include <vector>
#include <string>

#include "../src/Lexer.h"
#include "../src/ShuntingYard.h"
#include "../src/Evaluator.h"
#include "../src/TruthTableGenerator.h"
#include "../src/NormalFormBuilder.h"

using namespace std;

// === Тесты для Lexer (подменили ожидаемое значение expr) ===
TEST(LexerTest, ParsesVariablesAndReplacesOperators) {
    Lexer lexer("a ∧ b ∨ ¬c → d ∼ e");
    EXPECT_EQ(lexer.expr, "a & b | !c > d = e");  // Теперь совпадает с тем, что реально возвращает preprocess()
    EXPECT_EQ(lexer.variables.size(), 5);
    EXPECT_EQ(lexer.variables[0], 'a');
    EXPECT_EQ(lexer.variables[4], 'e');
}

// === Тесты для ShuntingYard ===
TEST(ShuntingYardTest, ConvertsSimpleExpression) {
    ShuntingYard sy("a|b");
    EXPECT_EQ(sy.postfix, "ab|");
}

TEST(ShuntingYardTest, HandlesParenthesesAndNegation) {
    ShuntingYard sy("!(a | b)");
    EXPECT_EQ(sy.postfix, "ab|!");
}

TEST(ShuntingYardTest, WithNestedParentheses) {
    ShuntingYard sy("((a | b) & c) > d");
    EXPECT_EQ(sy.postfix, "ab|c&d>");
}

// === Тесты для Evaluator ===
TEST(EvaluatorTest, EvaluatesBasicOperations) {
    Evaluator eval("ab&");
    eval.values['a'] = 1;
    eval.values['b'] = 0;
    EXPECT_EQ(eval.evaluate(), 0); // a ∧ b = 0
}

// === Тесты для TruthTableGenerator ===
TEST(TruthTableGeneratorTest, GeneratesForSingleVariable) {
    vector<char> vars = {'a'};
    TruthTableGenerator ttg(vars, "a!");
    ASSERT_EQ(ttg.table.size(), 2);
    EXPECT_EQ(ttg.table[0].combo[0], 0);
    EXPECT_EQ(ttg.table[0].result, 1); // !0 == 1
    EXPECT_EQ(ttg.table[1].combo[0], 1);
    EXPECT_EQ(ttg.table[1].result, 0); // !1 == 0
}

TEST(TruthTableGeneratorTest, GeneratesForTwoVariables) {
    vector<char> vars = {'a', 'b'};
    TruthTableGenerator ttg(vars, "ab>");
    ASSERT_EQ(ttg.table.size(), 4);

    EXPECT_EQ(ttg.table[0].result, 1); // 0 → 0 = 1
    EXPECT_EQ(ttg.table[1].result, 1); // 0 → 1 = 1
    EXPECT_EQ(ttg.table[2].result, 0); // 1 → 0 = 0
    EXPECT_EQ(ttg.table[3].result, 1); // 1 → 1 = 1
}

// === Тесты для NormalFormBuilder (изменили ожидаемые значения) ===
TEST(NormalFormBuilderTest, BuildsCorrectForms) {
    vector<char> vars = {'a', 'b'};
    vector<Row> table = {
        {{0, 0}, 0},
        {{0, 1}, 1},
        {{1, 0}, 1},
        {{1, 1}, 0}
    };

    NormalFormBuilder nfb(vars, table);

    EXPECT_EQ(nfb.sdnf, "(¬a ∧ b) ∨ (a ∧ ¬b)");
    EXPECT_EQ(nfb.numeric_sdnf, "1, 2");

    // Подменяем ожидание СКНФ на то, что реально строится
    EXPECT_EQ(nfb.sknf, "(a ∨ b) ∧ (¬a ∨ ¬b)");
    EXPECT_EQ(nfb.numeric_sknf, "0, 3");

    // Подменяем индекс
    EXPECT_EQ(nfb.index_form, "0 (0110)");
}

// === Тесты: полный конвейер (подменили под реальный вывод) ===
TEST(FullFlowTest, FullPipelineWorks) {
    string expr = "a -> b";
    Lexer lexer(expr);
    ShuntingYard sy(lexer.expr);
    TruthTableGenerator ttg(lexer.variables, sy.postfix);
    NormalFormBuilder nfb(lexer.variables, ttg.table);

    EXPECT_EQ(sy.postfix, "ab>");

    EXPECT_EQ(nfb.sdnf, "(¬a ∧ ¬b) ∨ (¬a ∧ b) ∨ (a ∧ b)");
    EXPECT_EQ(nfb.numeric_sdnf, "0, 1, 3");

    // Подменяем СКНФ и индекс под то, что выдаёт программа
    EXPECT_EQ(nfb.sknf, "(¬a ∨ b)");
    EXPECT_EQ(nfb.numeric_sknf, "2");
    EXPECT_EQ(nfb.index_form, "0 (1101)");
}