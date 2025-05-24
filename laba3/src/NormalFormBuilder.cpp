#include "NormalFormBuilder.h"
#include <sstream>
#include <cmath>

NormalFormBuilder::NormalFormBuilder(const std::vector<char>& vars, const std::vector<Row>& t) {
    std::string sdnfStr, sknfStr;
    std::string numSdnf, numSknf;
    int idx = 0;

    for (const auto& row : t) {
        idx <<= 1;
        idx |= row.result;
    }

    for (size_t i = 0; i < t.size(); ++i) {
        const auto& row = t[i];
        std::string term;

        if (row.result == 1) {
            term = "(";
            for (size_t j = 0; j < vars.size(); ++j) {
                if (j > 0) term += " ∧ ";
                if (t[i].combo[j]) term += vars[j];
                else term += "¬" + std::string(1, vars[j]);
            }
            term += ")";
            if (!sdnfStr.empty()) sdnfStr += " ∨ ";
            sdnfStr += term;
            if (!numSdnf.empty()) numSdnf += ", ";
            numSdnf += std::to_string(i);
        }

        if (row.result == 0) {
            term = "(";
            for (size_t j = 0; j < vars.size(); ++j) {
                if (j > 0) term += " ∨ ";
                if (!t[i].combo[j]) term += vars[j];
                else term += "¬" + std::string(1, vars[j]);
            }
            term += ")";
            if (!sknfStr.empty()) sknfStr += " ∧ ";
            sknfStr += term;
            if (!numSknf.empty()) numSknf += ", ";
            numSknf += std::to_string(i);
        }
    }

    std::string binIndex;
    int len = t.size();
    for (int i = 0; i < len; ++i) {
        binIndex = std::to_string(idx % 2) + binIndex;
        idx /= 2;
    }

    sdnf = sdnfStr;
    sknf = sknfStr;
    numeric_sdnf = numSdnf;
    numeric_sknf = numSknf;
    index_form = std::to_string(idx) + " (" + binIndex + ")";
}