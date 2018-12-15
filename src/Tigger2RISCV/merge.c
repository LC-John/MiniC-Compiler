#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	char* input_file = NULL, *output_file = NULL;
	char cmd[1024];
	for (int i = 0; i < argc; i++)
		if (strcmp(argv[i], "-I") == 0 || strcmp(argv[i], "--input") == 0)
			input_file = strdup(argv[i+1]);
		else if (strcmp(argv[i], "-O") == 0 || strcmp(argv[i], "--output") == 0)
			output_file = strdup(argv[i+1]);
	if (input_file == NULL && output_file == NULL)
		sprintf(cmd, "minic2eeyore/minic2eeyore | eeyore2mid/eeyore2mid | mid2tigger/mid2tigger | tigger2riscv/tigger2riscv");
	else if (input_file != NULL && output_file == NULL)
		sprintf(cmd, "minic2eeyore/minic2eeyore < %s | eeyore2mid/eeyore2mid | mid2tigger/mid2tigger | tigger2riscv/tigger2riscv", input_file);
	else if (input_file == NULL && output_file != NULL)
		sprintf(cmd, "minic2eeyore/minic2eeyore | eeyore2mid/eeyore2mid | mid2tigger/mid2tigger | tigger2riscv/tigger2riscv > %s", output_file);
	else
		sprintf(cmd, "minic2eeyore/minic2eeyore < %s | eeyore2mid/eeyore2mid | mid2tigger/mid2tigger | tigger2riscv/tigger2riscv > %s", input_file, output_file);
	system(cmd);
	return 0;
}
