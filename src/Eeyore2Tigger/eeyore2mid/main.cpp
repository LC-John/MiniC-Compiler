#include "op.h"
#include "tree.h"
#include "eeyore2mid.tab.h"

extern TreeNode *gramma_root;

int main() {
	yyparse();

	gramma_root->GenCode();
}
