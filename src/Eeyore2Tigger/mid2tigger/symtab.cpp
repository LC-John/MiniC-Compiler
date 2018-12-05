#include "symtab.h"

map<string, int> SymTable::label2instr;
map<string, int> SymTable::var2index;
map<int, string> SymTable::index2var;
map<string, int> SymTable::reg2color;
map<int, string> SymTable::color2reg;

set<int> SymTable::precolored;
set<int> SymTable::initial;
set<int> SymTable::spilledVar;

set<int> SymTable::calleeSaveReg;
set<int> SymTable::callerSaveReg;
map<string, set<int>> SymTable::funUsedReg;
map<string, set<int>> SymTable::funUsedCalleeSaveReg;
map<string, set<int>> SymTable::funUsedCallerSaveReg;

map<string, int> SymTable::runStack;

int SymTable::stackPoint = 0;

int SymTable::varIndexCount = 0;

void DisplaySet(string info, set<int> symbolSet) {
    cerr << info << "	";
    for (auto index : symbolSet) {
        cerr << SymTable::index2var[index] << "	";
    }
    cerr << endl;
}

void SymTable::InsertLabel(string label, int instr) {
    if (label == "") {
        return;
    }
    label2instr[label] = instr;
}

int SymTable::LookupLabel(string label) {
    if (label == "") {
        return -1;
    }
    return label2instr[label];
}

int SymTable::LookupVar(string varia) { return var2index[varia]; }

void SymTable::InsertPrecolored(string varia) {
    if (var2index.find(varia) == var2index.end()) {
        var2index[varia] = varIndexCount;
        index2var[varIndexCount] = varia;
        varIndexCount += 1;
    }
    precolored.insert(var2index[varia]);
}

void SymTable::InsertInitial(string varia) {
    if (var2index.find(varia) == var2index.end()) {
        var2index[varia] = varIndexCount;
        index2var[varIndexCount] = varia;
        varIndexCount += 1;
    }
    initial.insert(var2index[varia]);
}
void SymTable::Precolored() {
    int regCount = 0;

    color2reg[regCount] = "x0";
    reg2color["R_x0"] = regCount++;

    color2reg[regCount] = "a0";
    reg2color["R_a0"] = regCount++;

    color2reg[regCount] = "a1";
    reg2color["R_a1"] = regCount++;

    color2reg[regCount] = "a2";
    reg2color["R_a2"] = regCount++;

    color2reg[regCount] = "a3";
    reg2color["R_a3"] = regCount++;

    color2reg[regCount] = "a4";
    reg2color["R_a4"] = regCount++;

    color2reg[regCount] = "a5";
    reg2color["R_a5"] = regCount++;

    color2reg[regCount] = "a6";
    reg2color["R_a6"] = regCount++;

    color2reg[regCount] = "a7";
    reg2color["R_a7"] = regCount++;

    color2reg[regCount] = "s0";
    reg2color["R_s0"] = regCount++;

    color2reg[regCount] = "s1";
    reg2color["R_s1"] = regCount++;

    color2reg[regCount] = "s2";
    reg2color["R_s2"] = regCount++;

    color2reg[regCount] = "s3";
    reg2color["R_s3"] = regCount++;

    color2reg[regCount] = "s4";
    reg2color["R_s4"] = regCount++;

    color2reg[regCount] = "s5";
    reg2color["R_s5"] = regCount++;

    color2reg[regCount] = "s6";
    reg2color["R_s6"] = regCount++;

    color2reg[regCount] = "s7";
    reg2color["R_s7"] = regCount++;

    color2reg[regCount] = "s8";
    reg2color["R_s8"] = regCount++;

    color2reg[regCount] = "s9";
    reg2color["R_s9"] = regCount++;

    color2reg[regCount] = "s10";
    reg2color["R_s10"] = regCount++;

    color2reg[regCount] = "s11";
    reg2color["R_s11"] = regCount++;

    color2reg[regCount] = "t0";
    reg2color["R_t0"] = regCount++;

    color2reg[regCount] = "t1";
    reg2color["R_t1"] = regCount++;

    color2reg[regCount] = "t2";
    reg2color["R_t2"] = regCount++;

    color2reg[regCount] = "t3";
    reg2color["R_t3"] = regCount++;

    color2reg[regCount] = "t4";
    reg2color["R_t4"] = regCount++;

    color2reg[regCount] = "t5";
    reg2color["R_t5"] = regCount++;

    color2reg[regCount] = "t6";
    reg2color["R_t6"] = regCount++;

    callerSaveReg.insert(reg2color["R_t0"]);
    callerSaveReg.insert(reg2color["R_t1"]);
    callerSaveReg.insert(reg2color["R_t2"]);
    callerSaveReg.insert(reg2color["R_t3"]);
    callerSaveReg.insert(reg2color["R_t4"]);
    callerSaveReg.insert(reg2color["R_t5"]);
    callerSaveReg.insert(reg2color["R_t6"]);

    callerSaveReg.insert(reg2color["R_a1"]);
    callerSaveReg.insert(reg2color["R_a2"]);
    callerSaveReg.insert(reg2color["R_a3"]);
    callerSaveReg.insert(reg2color["R_a4"]);
    callerSaveReg.insert(reg2color["R_a5"]);
    callerSaveReg.insert(reg2color["R_a6"]);
    callerSaveReg.insert(reg2color["R_a7"]);

    calleeSaveReg.insert(reg2color["R_s0"]);
    calleeSaveReg.insert(reg2color["R_s1"]);
    calleeSaveReg.insert(reg2color["R_s2"]);
    calleeSaveReg.insert(reg2color["R_s3"]);
    calleeSaveReg.insert(reg2color["R_s4"]);
    calleeSaveReg.insert(reg2color["R_s5"]);
    calleeSaveReg.insert(reg2color["R_s6"]);
    calleeSaveReg.insert(reg2color["R_s7"]);
    calleeSaveReg.insert(reg2color["R_s8"]);
    calleeSaveReg.insert(reg2color["R_s9"]);
    calleeSaveReg.insert(reg2color["R_s10"]);
    calleeSaveReg.insert(reg2color["R_s11"]);
}

void SymTable::SpillVariable(set<int> spilledNodes) {
    set_union(spilledVar.begin(), spilledVar.end(), spilledNodes.begin(),
              spilledNodes.end(), inserter(spilledVar, spilledVar.begin()));
}

string SymTable::OperaName(OpeKind kind) {
    switch (kind) {
    case OP_ADD:
        return " + ";
    case OP_MIN:
        return " - ";
    case OP_MUL:
        return " * ";
    case OP_DIV:
        return " / ";
    case OP_MOD:
        return " % ";
    case OP_GRT:
        return " > ";
    case OP_LET:
        return " < ";
    case OP_AND:
        return " && ";
    case OP_ORT:
        return " || ";
    case OP_EQT:
        return " == ";
    case OP_NET:
        return " != ";
    case OP_NEG:
        return " - ";
    case OP_NOT:
        return " ! ";
    }
    return "";
}

void SymTable::InsertStack(string varia) {
    if (runStack.find(varia) == runStack.end()) {
        runStack[varia] = stackPoint;
        stackPoint += 1;
    }
}

void SymTable::InsertStack(string varia, int memory) {
    if (runStack.find(varia) == runStack.end()) {
        runStack[varia] = stackPoint;
        stackPoint += memory / 4;
    }
}

int SymTable::LookupStack(string varia) { return runStack[varia]; }

void SymTable::FunctionUsedReg(string funct, set<int> usedReg) {
    funUsedReg[funct] = usedReg;

    set<int> saveReg;

    saveReg.clear();
    set_intersection(callerSaveReg.begin(), callerSaveReg.end(),
                     usedReg.begin(), usedReg.end(),
                     inserter(saveReg, saveReg.begin()));
    funUsedCallerSaveReg[funct] = saveReg;

    saveReg.clear();
    set_intersection(calleeSaveReg.begin(), calleeSaveReg.end(),
                     usedReg.begin(), usedReg.end(),
                     inserter(saveReg, saveReg.begin()));
    funUsedCalleeSaveReg[funct] = saveReg;
}
