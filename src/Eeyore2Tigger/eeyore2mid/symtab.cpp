#include "symtab.h"

map<string, string> SymTable::globalVar;
map<string, bool> SymTable::localVar;
map<string, bool> SymTable::arrayVar;

string SymTable::OperaName(OpeKind kind)
{
    switch (kind)
    {
    case OP_ADD:
        return " + ";
    case OP_SUB:
        return " - ";
    case OP_MUL:
        return " * ";
    case OP_DIV:
        return " / ";
    case OP_MOD:
        return " % ";
    case OP_GT:
        return " > ";
    case OP_LT:
        return " < ";
    case OP_AND:
        return " && ";
    case OP_OR:
        return " || ";
    case OP_EQ:
        return " == ";
    case OP_NEQ:
        return " != ";
    case OP_NEG:
        return " - ";
    case OP_NOT:
        return " ! ";
    default:
	return "  ";
    }
    return "";
}

bool SymTable::IsGlobal(string varia)
{
    return globalVar.find(varia) != globalVar.end();
}

string SymTable::InsertGlobal(string varia)
{
	globalVar[varia] = Counter::GenGlobaCode();
	return globalVar[varia];
}

string SymTable::GlobalVar(string varia)
{
    if (IsGlobal(varia))
        return globalVar[varia];
    else
        return "";
}

bool SymTable::IsLocal(string varia)
{
    return localVar.find(varia) != localVar.end();
}

void SymTable::InsertLocal(string varia)
{
	localVar[varia] = true;
}

bool SymTable::IsArray(string varia)
{
    return arrayVar.find(varia) != arrayVar.end();
}

void SymTable::InsertArray(string varia)
{
	arrayVar[varia] = true;
}
