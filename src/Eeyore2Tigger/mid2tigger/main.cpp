#include "conflictgraph.h"
#include "tree.h"
#include "op.h"
#include "mid2tigger.tab.h"
#include "flowgraph.h"
#include "symtab.h"

Graph ConflictGraph;
extern vector<TreeNode *> worklist_sequence;
extern TreeNode *gramma_root;

void BuildInsGraph()
{
    for (int i = 0; i < worklist_sequence.size(); i++)
    {
        SymTable::InsertLabel(worklist_sequence[i]->LabelName(), i);
	InsGraph::InsertGraphNode(worklist_sequence[i]);
    }
    for (int i = 0; i < worklist_sequence.size(); i++)
    {
        if (worklist_sequence[i]->NextInSucc())
            InsGraph::AddEdge(worklist_sequence[i], worklist_sequence[i + 1]);
        int succ = SymTable::LookupLabel(worklist_sequence[i]->LabelInSucc());
        if (succ != -1)
            InsGraph::AddEdge(worklist_sequence[i], worklist_sequence[succ]);
    }
}

void CalculateDefUse()
{
    for (int i = 0; i < worklist_sequence.size(); i++)
    {
        InsGraphNode *insNode = InsGraph::LookupInsGraphNode(worklist_sequence[i]);
        insNode->def = worklist_sequence[i]->GetDefSymbol();
        insNode->use = worklist_sequence[i]->GetUseSymbol();
    }
}

int main()
{
    yyparse();

    do
    {
        InsGraph::ins2Node.clear();
	InsGraph::insVector.clear();
        BuildInsGraph();
        CalculateDefUse();
	InsGraph::LivenessAnalysis();
    } while (!ConflictGraph.Main());

    gramma_root->LookupUsedReg();
    gramma_root->TransTigger("");
}
