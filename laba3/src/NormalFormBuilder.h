#ifndef NORMALFORMBUILDER_H
#define NORMALFORMBUILDER_H

#include <vector>
#include <string>
#include "TruthTableGenerator.h"

class NormalFormBuilder {
public:
    std::string sdnf, sknf;
    std::string numeric_sdnf, numeric_sknf;
    std::string index_form;

    NormalFormBuilder(const std::vector<char>& vars, const std::vector<Row>& t);
};

#endif // NORMALFORMBUILDER_H