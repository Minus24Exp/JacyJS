#ifndef CODEGEN_H
#define CODEGEN_H

#include <string>
#include "tree/nodes.h"
#include "Exception.h"

using str = std::string;

class Codegen {
public:
    Codegen();
    virtual ~Codegen() = default;

    str literal(Literal * literal);
    str op_method(const Token & token);
};

#endif
