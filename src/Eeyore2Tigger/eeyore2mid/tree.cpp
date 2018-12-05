#include "tree.h"

string StmNode::GenCode()
{
    switch (kind)
    {
    case GOTOIF_KIND:
    {
        string condi = child[0]->GenUseCode();
        string label = child[1]->GenCode();
        cout << "if " << condi << " goto " << label << endl;
        break;
    }
    case GOTODO_KIND:
    {
        string label = child[0]->GenCode();
        cout << "goto " << label << endl;
        break;
    }
    case PARAME_KIND:
    {
        string paramIdx = Counter::GenParamCode();
        string paramIde = child[0]->GenUseCode();
        cout << paramIdx << " = " << paramIde << endl;
        break;
    }
    case RETURN_KIND:
    {
        string paramRet = child[0]->GenUseCode();
        cout << "R_a0 = " << paramRet << endl;
        cout << "return" << endl;
        break;
    }
    case ASSIGN_KIND:
    {
        string lvalue = child[0]->GenDefCode();
        string rvalue = child[1]->GenUseCode();
        cout << lvalue << " = " << rvalue << endl;
        break;
    }
    case FUNDEF_KIND:
    {
        string funct = child[0]->GenCode();
        string parac = child[1]->GenUseCode();
        cout << funct << " [ " << parac << " ] " << endl;
        for (int i = 0; i < atoi(parac.c_str()); i++)
            cout << "L_p" << i << " = " << "R_a" << i << endl;
        child[2]->GenCode();
	cout << "return" << endl;
        cout << "end " << funct << endl;
    }
    case VARDEF_KIND:
        if (this->globalStm)
        {
            string varia = child[0]->GetName();
            string globv = SymTable::InsertGlobal(varia);
            cout << globv << " = 0" << endl;
        }
        break;
    case LABELT_KIND:
    {
        string label = child[0]->GenCode();
        cout << label << " :" << endl;
        break;
    }
    case ARRDEF_KIND:
        if (this->globalStm)
        {
            string varia = child[1]->GetName();
            string asize = child[0]->GenUseCode();
            string globv = SymTable::InsertGlobal(varia);
            SymTable::InsertArray(varia);
            cout << globv << " = malloc " << asize << endl;
        } 
        else
        {
            string varia = child[1]->GetName();
            string asize = child[0]->GenUseCode();
            SymTable::InsertLocal(varia);
            SymTable::InsertArray(varia);
            cout << "push " << varia << " " << asize << endl;
        }
        break;
    case SEQUEN_KIND:
        if (child[0] != nullptr)
            child[0]->GenCode();
        if (child[1] != nullptr)
            child[1]->GenCode();
    default: break;
    }
    return "";
}

string VariaExpNode::GenUseCode()
{
    if (SymTable::IsGlobal(varia))
    {
        if (SymTable::IsArray(varia))
        {
            string tempv = Counter::GenTempoCode();
            string globv = SymTable::GlobalVar(varia);
            cout << "loadaddr " << globv << " " << tempv << endl;
            return tempv;
        }
        else
        {
            string temp1 = Counter::GenTempoCode();
            string temp2 = Counter::GenTempoCode();
            string globv = SymTable::GlobalVar(varia);
            cout << "loadaddr " << globv << " " << temp1 << endl;
            cout << temp2 << " = " << temp1 << "[0]" << endl;
            return temp2;
        }
    }
    if (SymTable::IsLocal(varia))
    {
        if (SymTable::IsArray(varia))
        {
            cout << "loadaddr " << varia << endl;
            return varia;
        }
        else
        {
            string tempv = Counter::GenTempoCode();
            cout << "loadaddr " << varia << endl;
            cout << tempv << " = " << varia << "[0]" << endl;
            return tempv;
        }
    }
    return varia;
}

string VariaExpNode::GenDefCode()
{
    if (SymTable::IsGlobal(varia))
    {
        if (SymTable::IsArray(varia))
        {
            string tempv = Counter::GenTempoCode();
            string globv = SymTable::GlobalVar(varia);
            cout << "loadaddr " << globv << " " << tempv << endl;
            return tempv;
        }
	else
        {
            string temp1 = Counter::GenTempoCode();
            string globv = SymTable::GlobalVar(varia);
            cout << "loadaddr " << globv << " " << temp1 << endl;
            return temp1 + "[0]";
        }
    }
    if (SymTable::IsLocal(varia))
    {
        if (SymTable::IsArray(varia))
        {
            cout << "loadaddr " << varia << endl;
            return varia;
        }
        else
        {
            cout << "loadaddr " << varia << endl;
            return varia + "[0]";
        }
    }
    return varia;
}

string Oper1ExpNode::GenUseCode()
{
    string rval1 = child[0]->GenUseCode();
    string opstr = SymTable::OperaName(opera);
    return opstr + rval1;
}

string Oper2ExpNode::GenUseCode()
{
    string rval1 = child[0]->GenUseCode();
    string rval2 = child[1]->GenUseCode();
    string opstr = SymTable::OperaName(opera);
    return rval1 + opstr + rval2;
}

string CallfExpNode::GenUseCode()
{
    string tempv = Counter::GenTempoCode();
    Counter::ParamCountInit();
    cout << "call " << funct << endl;
    cout << tempv << " = R_a0" << endl;
    return tempv;
}
