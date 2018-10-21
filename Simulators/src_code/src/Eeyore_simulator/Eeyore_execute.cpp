#include "typedef.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <stack>
#include <cctype>
#include <cstdlib>
using namespace std;
extern vector<ins> com_ins;
extern unordered_map<unsigned, unordered_map<int, int>> f_symbol;
extern unordered_map<unsigned, vector<pair<int, int>>> f_arr;
vector<int> global_ins;
unordered_map<int, int> gsymbol;

const int  param[] = {0x3, 0x7, 0xb, 0xf, 0x13, 0x17, 0x1b, 0x1f, 0x23, 0x27};
#define getI(x) (((x) & 3) ? getValue(x, symbol) : (x) >> 2)
#define setValue(x, y) {if(symbol.find(x) != symbol.end()) symbol[x] = y; else gsymbol[x] = y;}
int getValue(int x, unordered_map<int, int> & symbol){
	if(symbol.find(x) != symbol.end())
		return symbol[x];
	if(gsymbol.find(x) != gsymbol.end())
		return gsymbol[x];
	cout << "Error! Can't find the symbol -- " << x  << endl;
	return -1;
}

int exe_op2(int src1, int src2, int op){
    char _op = op;
		switch(_op){
			case '+':
				return src1 + src2;
			case '-':
				return src1 - src2;
			case '*':
				return src1 * src2;
			case '/':
				return src1 / src2;
			case '%':
				return src1 % src2;
			case '<':
				return src1 < src2;
			case '>':
				return src1 > src2;
			case '|':
				return src1 || src2;
			case '&':
				return src1	&& src2;
			case '!':
				return src1 != src2;
			case '=':
				return src1 == src2;
			default:
				;
				//Error
	}
	return -1;
}
int exe_op1(int src1, int op){
    char _op = op;
		switch(_op){
			case '-':
				return -src1;
			case '!':
				return !src1;
			default:
				;
				//Error
		}
	return -1;
}
bool isBuildIn(int a){
    //-1: f_getint
    //-2: f_putint
    //-3: f_putchar
    return a < 0;
}
int callBuildIn(int a, stack<int> & stk){
    //-1: f_getint
    //-2: f_putint
    //-3: f_putchar
    int tmp;
    if(a == -1){
        //cin >> tmp;
        scanf("%d",&tmp);
        return tmp;
    }
    if(a == -2){
        tmp = stk.top();
        stk.pop();
        //cout << tmp;
        printf("%d", tmp);
        return 0;
    }
    if(a == -3){
        tmp = stk.top();
        stk.pop();
        //cout << (char)tmp;
        printf("%c", (char)tmp);
        return 0;
    }
    if(a == -4){
        char tmp;
        scanf("%c", &tmp);
        return tmp;
    }
    return 0;
}

int callFunction(unsigned long pc, unsigned long ori_pc, unsigned long arg_size, stack<int> & arg){
	unordered_map<int, int> symbol = f_symbol[pc];
    for(auto x : f_arr[pc])
        symbol[x.first] = (int)malloc(x.second);
	stack<int> arg_s;

    //cout << "DEBUG " << arg_size << endl;

	//Initial argument
	for(int i = arg_size; i > 0; i--){
		int tmp = arg.top();
		arg.pop();
		symbol[param[i - 1]] = tmp;
	}

	void debugFunc(unsigned long pc, unordered_map<int, int> & lo_symbol);
	while(1){
        //cout << "PC: " << pc << endl;
		ins t = com_ins[pc];
		if(t.type != iNOOP)
			debugFunc(pc, symbol);
		pc += 1;
		int src1, src2, src3, des;
		switch(t.type){
			case iNOOP:
				break;
			case iOP2:
				src1 = getI(t.arg2);
				src2 = getI(t.arg4);
				des = exe_op2(src1 ,src2, t.arg3);
				setValue(t.arg1, des);
				break;
			case iOP1:
				src1 = getI(t.arg3);
				des = exe_op1(src1, t.arg2);
				setValue(t.arg1, des);
				break;
			case iASS:
				des = getI(t.arg2);
				setValue(t.arg1, des);
				break;
			case iARRSET:
				src1 = getI(t.arg1);
				src2 = getI(t.arg2);
				des = getI(t.arg3);
				src1 += src2;
				*((int*)src1) = des;
				break;
			case iARRGET:
				src1 = getI(t.arg2);
				src2 = getI(t.arg3);
				src1 += src2;
				des = *((int*)src1);
				setValue(t.arg1, des);
				break;
			case iIF:
				src1 = getI(t.arg1);
				src2 = getI(t.arg3);
				if(exe_op2(src1, src2, t.arg2))
					pc = t.arg4;
				break;
			case iGOTO:
				pc = t.arg1;
				break;
			case iPARAM:
				arg_s.push(getI(t.arg1));
				break;
			case iCALLVOID:
                if(isBuildIn(t.arg1))
                    callBuildIn(t.arg1, arg_s);
                else
				    callFunction(t.arg1, pc, t.arg2, arg_s);
				break;
			case iCALL:
                if(isBuildIn(t.arg2))
                    des = callBuildIn(t.arg2, arg_s);
                else
				    des = callFunction(t.arg2, pc, t.arg3, arg_s);
				setValue(t.arg1, des);
				break;
			case iRETURN:
				if(t.arg1 == 0)
					return 0;
				else
					return getI(t.arg1);
				break;
			default:
				;
				//Error
		}
	}
}

int beginProgram(unsigned long pc){
	stack<int> arg;
    gsymbol = f_symbol[0];
	auto & symbol = gsymbol;
	unsigned long tmp = 0;
    for(auto x : f_arr[0])
        symbol[x.first] = (int)malloc(x.second);

/*
    for(int i = 0; i < com_ins.size(); ++i){
        cout << "i: " << i << " INS: " << com_ins[i].type
            << " " << com_ins[i].arg1
            << " " << com_ins[i].arg2
            << " " << com_ins[i].arg3
            << " " << com_ins[i].arg4
            << endl;
    }
*/
	for(auto x : global_ins){
        //cout << "GL: " << x << endl;
		ins t = com_ins[x];
		int src1, src2, src3, des;
		switch(t.type){
			case iNOOP:
				break;
			case iOP2:
				src1 = getI(t.arg2);
				src2 = getI(t.arg4);
				des = exe_op2(src1 ,src2, t.arg3);
				setValue(t.arg1, des);
				break;
			case iOP1:
				src1 = getI(t.arg3);
				des = exe_op1(src1, t.arg2);
				setValue(t.arg1, des);
				break;
			case iASS:
				des = getI(t.arg2);
				setValue(t.arg1, des);
				break;
			case iARRSET:
				src1 = getI(t.arg1);
				src2 = getI(t.arg2);
				des = getI(t.arg3);
				src1 += src2;
				*((int*)src1) = des;
				break;
			case iARRGET:
				src1 = getI(t.arg2);
				src2 = getI(t.arg3);
				src1 += src2;
				des = *((int*)src1);
				setValue(t.arg1, des);
				break;
			default:
				;
			}
	}
	return callFunction(pc, -1, 0, arg);
}
