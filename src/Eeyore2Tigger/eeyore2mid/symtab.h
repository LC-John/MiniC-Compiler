#ifndef __SYMTAB_H__
#define __SYMTAB_H__

#include "count.h"
#include "op.h"

class SymTable
{
    static map<string, string> globalVar;
    static map<string, bool> localVar;
    static map<string, bool> arrayVar;

public:
    static string OperaName(OpeKind kind);

    static bool IsGlobal(string varia);
    static string InsertGlobal(string varia);
    static string GlobalVar(string varia);

    static bool IsLocal(string varia);
    static void InsertLocal(string varia);

    static bool IsArray(string varia);
    static void InsertArray(string varia);
};

#endif
