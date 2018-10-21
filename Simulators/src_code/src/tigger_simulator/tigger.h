#ifndef TIGGER_H
#define TIGGER_H

#include <vector>
#include <map>
#include <string>
#include <stack>
#include "tigger.tab.hpp"

struct statement_t;

//extern std::vector<int> stackmem;
//#define STACKNUM 1000000

//extern int stackmem[STACKNUM];
extern int reg[REGNUM];
extern std::vector<int*> gvars;
extern std::vector<statement_t *> stmts;
extern std::map<int, int> labels;
extern std::map<std::string, int> funcs;
extern std::map<int, int> gvar_name;
extern int ngvar;
extern int pc, *st, ssp;
struct CallStack_t {
    int pc; /* program counter */
    //int sp; /* stack pointer */
    int *st;
    int ssp; /* stack space to use */
    CallStack_t(int _pc, int *_st, int _ssp): pc(_pc), st(_st), ssp(_ssp) {}
};
extern std::stack<CallStack_t> callstack;
extern const char *str_reg[REGNUM];
int find_reg(const char *s);

#endif
