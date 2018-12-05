#ifndef __TREE_H__
#define __TREE_H__

#include "count.h"
#include "symtab.h"
#include "op.h"

enum NodKind { STM_KIND, EXP_KIND };

enum ExpKind {
    OPERA_KIND,
    INTEG_KIND,
    VARIA_KIND,
    ARRAY_KIND,
    FUNCT_KIND,
    CALLF_KIND,
    LABEL_KIND
};

enum StmKind {
    GOTODO_KIND,
    GOTOIF_KIND,
    PARAME_KIND,
    RETURN_KIND,
    LABELT_KIND,
    ASSIGN_KIND,
    VARDEF_KIND,
    ARRDEF_KIND,
    FUNDEF_KIND,
    SEQUEN_KIND
};

class TreeNode {
  private:
    static const int MAX_CHILDREN = 3;

  public:
    TreeNode *child[MAX_CHILDREN];
    NodKind nodeKind;

    TreeNode(NodKind nodeKind) {
        this->nodeKind = nodeKind;

        for (int i = 0; i < MAX_CHILDREN; i++) {
            child[i] = NULL;
        }
    }

    virtual string GetName() {}
    virtual void SetGlobal() {}
    virtual string GenCode() {}
    virtual string GenDefCode() {}
    virtual string GenUseCode() {}
};

class StmNode : public TreeNode {
  public:
    StmKind kind;
    bool globalStm;

    StmNode(StmKind kind) : TreeNode(STM_KIND) { this->kind = kind; }
    void SetGlobal() { this->globalStm = true; }
    string GenCode();
};

class ExpNode : public TreeNode {
  public:
    ExpKind kind;

    ExpNode(ExpKind kind) : TreeNode(EXP_KIND) { this->kind = kind; }
};

class VariaExpNode : public ExpNode {
  public:
    string varia;

    VariaExpNode(string varia) : ExpNode(VARIA_KIND) { this->varia = varia; }
    string GetName() { return varia; }
    string GenDefCode();
    string GenUseCode();
};

class LabelExpNode : public ExpNode {
  public:
    string label;

    LabelExpNode(string label) : ExpNode(LABEL_KIND) { this->label = label; }
    string GetName() { return label; }
    string GenCode() { return GetName(); }
};

class FunctExpNode : public ExpNode {
  public:
    string funct;

    FunctExpNode(string funct) : ExpNode(FUNCT_KIND) { this->funct = funct; }
    string GetName() { return funct; }
    string GenCode() { return GetName(); }
};

class Oper2ExpNode : public ExpNode {
  public:
    OpeKind opera;

    Oper2ExpNode(OpeKind opera) : ExpNode(OPERA_KIND) { this->opera = opera; }
    string GenUseCode();
};

class Oper1ExpNode : public ExpNode {
  public:
    OpeKind opera;

    Oper1ExpNode(OpeKind opera) : ExpNode(OPERA_KIND) { this->opera = opera; }
    string GenUseCode();
};

class CallfExpNode : public ExpNode {
  public:
    string funct;

    CallfExpNode(string funct) : ExpNode(CALLF_KIND) { this->funct = funct; }
    string GenUseCode();
};

class IntegExpNode : public ExpNode {
  public:
    int value;

    IntegExpNode(string value) : ExpNode(INTEG_KIND) {
        stringstream cout;
        cout << value;
        cout >> this->value;
    }
    string GenUseCode() { return std::to_string(value); }
};

class ArrayExpNode : public ExpNode {
  public:
    string varia;

    ArrayExpNode(string varia) : ExpNode(ARRAY_KIND) { this->varia = varia; }
    string GenDefCode() { return varia + "[0]"; }
    string GenUseCode() { return varia + "[0]"; }
};

#endif
