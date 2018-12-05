#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

enum OpeKind {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_GT,
    OP_LT,
    OP_AND,
    OP_OR,
    OP_EQ,
    OP_NEQ,
    OP_NEG,
    OP_NOT
};

#endif
