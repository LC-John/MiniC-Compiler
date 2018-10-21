#include "typedef.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
using namespace std;

int yyparse (void);
extern FILE * yyin;

void help(const char * path) {
    cout << "Usage: " << path << " [-d] <filename>" << endl;
}

vector<string> ori_ins;
vector<ins> com_ins;
unordered_map<string, unsigned> farg;
unordered_map<string, unsigned> label_table;
unordered_map<unsigned, unordered_map<int, int>> f_symbol;
unordered_map<unsigned,vector<pair<int, int>>> f_arr;
vector<_store> relocated;

void relocate(){
    for(auto x : relocated){
        if(x.label[0] == 'l'){
            switch(x.pos){
                case 0:
                    com_ins[x.index].arg1 = label_table[x.label];
                    continue;
                case 1:
                    com_ins[x.index].arg2 = label_table[x.label];
                    continue;
                case 2:
                    com_ins[x.index].arg3 = label_table[x.label];
                    continue;
                case 3:
                    com_ins[x.index].arg4 = label_table[x.label];
                    continue;
            }
        }
        else{
            switch(x.pos){
                case 0:
                    com_ins[x.index].arg1 = label_table[x.label];
                    com_ins[x.index].arg2 = farg[x.label];
                    continue;
                case 1:
                    com_ins[x.index].arg2 = label_table[x.label];
                    com_ins[x.index].arg3 = farg[x.label];
                    continue;
            }
        }
    }
}
unsigned long pc = 1;
int main(int argc, char** argv){
	bool debugMode = false;

	ifstream is;
    //Analyze the arguments
    if(argc == 2){
        is.open(argv[1]);
        yyin = fopen(argv[1], "r");
    }
    else if(argc == 3 && argv[1] == string("-d")){
        debugMode = true;
        is.open(argv[2]);
        yyin = fopen(argv[2], "r");
    }
    else{
        help(argv[0]);
        exit(-1);
    }

    //Get the original code
    while (!is.eof()) {
        string tmp;
        getline(is, tmp);
        ori_ins.push_back(tmp);
    }

	//Compile the instruction
	com_ins.resize(ori_ins.size() + 1);
    f_symbol[0] = unordered_map<int, int>();
    f_arr[0] = vector<pair<int, int>>();
	yyparse();

    label_table["f_getint"] = -1;
    label_table["f_putint"] = -2;
    label_table["f_putchar"] = -3;
    label_table["f_getchar"] = -4;
    relocate();

    //cout << "DEBUG" << endl;
    //for(auto x : label_table){
    //    cout << x.first << " " << x.second << endl;
    //}
	pc = (unsigned)label_table["f_main"];

	void initialDebug(bool);
	initialDebug(debugMode);

	int beginProgram(unsigned long pc);
	return beginProgram(pc);
}
