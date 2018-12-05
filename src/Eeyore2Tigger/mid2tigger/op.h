#ifndef __OP_H__
#define __OP_H__

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

enum OpeKind {
    OP_ADD,
    OP_MIN,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_GRT,
    OP_LET,
    OP_AND,
    OP_ORT,
    OP_EQT,
    OP_NET,
    OP_NEG,
    OP_NOT
};

#endif
