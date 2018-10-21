#include "yaccTypes.h"
#include "tigger.h"
#include <functional>
#include <cstdlib>

void stmt_func_begin::run()
{
    ssp = stackSlotNum;
    st = new int[stackSlotNum];
    //sp += stackSlotNum;
    //stackmem.resize(stackmem.size() + stackSlotNum);
    ++pc;
}

void stmt_return::run()
{
    if (callstack.empty())
        exit(reg[find_reg("a0")]);
    CallStack_t t = callstack.top();
    callstack.pop();
    ssp = t.ssp;
    st = t.st;
    pc = t.pc + 1;
}

void stmt_func_end::run()
{
    printf("reach function end with no return statement");
    exit(1);
}

void stmt_assign_const::run()
{
    reg[rnum] = value;
    ++pc;
}

void stmt_assign_op2::run()
{
    static std::map<std::string, std::function<int(int, int)>> op2{
        {"+", [](int a, int b) {return a + b;}},
        {"-", [](int a, int b) {return a - b;}},
        {"*", [](int a, int b) {return a * b;}},
        {"/", [](int a, int b) {return a / b;}},
        {"%", [](int a, int b) {return a % b;}},
        {">", [](int a, int b) {return a > b;}},
        {"<", [](int a, int b) {return a < b;}},
        {">=", [](int a, int b) {return a >= b;}},
        {"<=", [](int a, int b) {return a <= b;}},
        {"&&", [](int a, int b) {return a && b;}},
        {"||", [](int a, int b) {return a || b;}},
        {"!=", [](int a, int b) {return a != b;}},
        {"==", [](int a, int b) {return a == b;}}
    };
    reg[dest] = op2[op](reg[src1], reg[src2]);
    ++pc;
}

void stmt_assign_op2i::run()
{
    static std::map<std::string, std::function<int(int, int)>> op2{
        {"+", [](int a, int b) {return a + b;}},
        {"<", [](int a, int b) {return a < b;}}
    };
    reg[dest] = op2[op](reg[src1], value);
    ++pc;
}

void stmt_assign_op1::run()
{
    static std::map<std::string, std::function<int(int)>> op1{
        {"+", [](int a) {return a;}},
        {"-", [](int a) {return -a;}},
        {"*", [](int a) {return *(int *)a;}},
        {"!", [](int a) {return !a;}},
    };
    reg[dest] = op1[op](reg[src]);
    ++pc;
}

void stmt_assign_lidx::run()
{
    char *ptr = (char *)reg[dest];
    *(int *)(ptr + idx) = reg[src];
    ++pc;
}

void stmt_assign_move::run()
{
    reg[dest] = reg[src];
    ++pc;
}

void stmt_assign_ridx::run()
{
    char *ptr = (char *)reg[src];
    reg[dest] = *(int *)(ptr + idx);
    ++pc;
}

void stmt_if_goto::run()
{
    static std::map<std::string, std::function<int(int, int)>> rop{
        {">", [](int a, int b) {return a > b;}},
        {"<", [](int a, int b) {return a < b;}},
        {">=", [](int a, int b) {return a >= b;}},
        {"<=", [](int a, int b) {return a <= b;}},
        {"&&", [](int a, int b) {return a && b;}},
        {"||", [](int a, int b) {return a || b;}},
        {"!=", [](int a, int b) {return a != b;}},
        {"==", [](int a, int b) {return a == b;}}
    };
    if (rop[op](reg[src1], reg[src2]))
        pc = labels[lnum];
    else
        ++pc;
}

void stmt_goto::run()
{
    pc = labels[lnum];
}

void stmt_call::run()
{
    if (name == "getint") {
        scanf("%d", &reg[find_reg("a0")]);
        ++pc;
    }
    else if (name == "putint") {
        printf("%d", reg[find_reg("a0")]);
        ++pc;
    }
    else if (name == "getchar") {
        char c;
        scanf("%c", &c);
        reg[find_reg("a0")] = c;
        ++pc;
    }
    else if (name == "putchar") {
        printf("%c", (char)reg[find_reg("a0")]);
        ++pc;
    }
    else {
        callstack.push(CallStack_t(pc, st, ssp));
        pc = funcs[name];
    }
}

void stmt_label::run()
{
    ++pc;
}

/*void stmt_malloc::run()
{
    if (sp + size / 4 > stackmem.size()) {
        printf("stack memery access error\n");
        exit(-1);
    }
    reg[rnum] = (int)&stackmem[sp];
    sp = sp + size / 4;
    ++pc;
}*/

void stmt_store_local::run()
{
    st[snum] = reg[rnum];
    ++pc;
}

/*
void stmt_store_global::run()
{
    if (xnum > ngvar) {
        printf("heap memery access error\n");
        exit(-1);
    }
    gvars[xnum] = reg[rnum];
    ++pc;
}
*/

void stmt_load_local::run()
{
    reg[rnum] = st[snum];
    ++pc;
}

void stmt_load_global::run()
{
    if (xnum > ngvar) {
        printf("heap memery access error\n");
        exit(-1);
    }
    reg[rnum] = *gvars[xnum];
    ++pc;
}

void stmt_loadaddr_local::run()
{
    reg[rnum] = (int)&st[snum];
    ++pc;
}

void stmt_loadaddr_global::run()
{
    if (xnum > ngvar) {
        printf("heap memery access error\n");
        exit(-1);
    }
    reg[rnum] = (int)gvars[xnum];
    ++pc;
}
