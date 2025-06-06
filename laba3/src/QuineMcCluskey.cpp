#include "QuineMcCluskey.h"
#include <algorithm>

QuineMcCluskey::QuineMcCluskey(const vector<vector<int>>& input_terms, const vector<char>& var_names) {
    vector<string> binaries = to_binary_strings(input_terms);
    vector<Minterm> grouped = group_terms(binaries);
    reduce_terms({grouped});
}

vector<string> QuineMcCluskey::minimize() {
    return simplified_terms;
}

vector<string> QuineMcCluskey::to_binary_strings(const vector<vector<int>>& terms) {
    vector<string> result;
    for (auto combo : terms) {
        std::stringstream ss;
        for (int b : combo) ss << b;
        result.push_back(ss.str());
    }
    return result;
}

vector<QuineMcCluskey::Minterm> QuineMcCluskey::group_terms(const vector<string>& binaries) {
    vector<Minterm> result;
    for (auto bin : binaries) {
        int ones = count(bin.begin(), bin.end(), '1');
        result.push_back({bin, ones, false});
    }
    return result;
}

void QuineMcCluskey::reduce_terms(const vector<vector<Minterm>>& groups) {
    simplified_terms.clear();
    map<string, bool> checked;

    for (auto group : groups) {
        for (auto m : group) {
            if (!m.used) simplified_terms.push_back(m.binary);
        }
    }
}

vector<QuineMcCluskey::Minterm> QuineMcCluskey::combine_terms(const Minterm& m1, const Minterm& m2) {
    vector<Minterm> result;
    int diff = 0;
    string combined;

    for (size_t i = 0; i < m1.binary.length(); ++i) {
        if (m1.binary[i] != m2.binary[i]) diff++;
    }

    if (diff == 1) {
        combined = "";
        for (size_t i = 0; i < m1.binary.length(); ++i) {
            if (m1.binary[i] == m2.binary[i])
                combined += m1.binary[i];
            else
                combined += "-";
        }
        result.push_back({combined, 0, false});
    }

    return result;
}

string QuineMcCluskey::decimal_to_binary(int num, int length) {
    string binary;
    while (length--) binary = (num % 2 ? "1" : "0") + binary, num /= 2;
    return binary;
}