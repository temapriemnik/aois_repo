#ifndef QUINEMCCLUSKEY_H
#define QUINEMCCLUSKEY_H

#include <vector>
#include <string>
#include <map>
#include "Utils.h"

class QuineMcCluskey {
public:
    struct Minterm {
        std::string binary;
        int ones;
        bool used;
    };

    vector<Minterm> minterms;
    vector<string> simplified_terms;

    QuineMcCluskey(const vector<vector<int>>& input_terms, const vector<char>& var_names);
    vector<string> minimize();

private:
    vector<string> to_binary_strings(const vector<vector<int>>& terms);
    vector<Minterm> group_terms(const vector<string>& binaries);
    vector<Minterm> combine_terms(const Minterm& m1, const Minterm& m2);
    void reduce_terms(const vector<vector<Minterm>>& groups);
    string decimal_to_binary(int num, int length);
};

#endif // QUINEMCCLUSKEY_H