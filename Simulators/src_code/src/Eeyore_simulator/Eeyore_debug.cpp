#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

static int debugMod = 1;
static size_t debugCount = 0;
extern vector<string> ori_ins;
extern unordered_map<int, int> gsymbol;
extern unordered_map<string, int> label_table;

unsigned var(const char* a);
void initialDebug(bool mod){
    debugMod = mod;
}
void intoDebug(unsigned long pc, unordered_map<int, int> & lo_symbol){
    string tmp;
    while(1){
        cout << "PC: " << pc << " " << ori_ins[pc - 1] << endl;
        cout << "> ";
        cin >> tmp;
        if(tmp == "p"){
            // Print symbol
            cin >> tmp;
            int _tmp = var(tmp.c_str());
            if(lo_symbol.find(_tmp) != lo_symbol.end()){
                cout << tmp << " " << lo_symbol[_tmp] << endl;
            }
            else{
                if(gsymbol.find(_tmp) != gsymbol.end()){
                    cout << tmp << " " << gsymbol[_tmp] << endl;
                    continue;
                }
                cout << "No such symbol found in the scope." << endl;
            }
            continue;
        }
        if(tmp == "s"){
            // Step in
            int nStep = 0;
            cin >> nStep;
            debugMod = 1;
            debugCount = nStep;
            return;
        }
        if(tmp == "n"){
            //next step
            debugMod = 1;
            debugCount = 1;
            return;
        }
        if(tmp == "u"){
            // Until
            cin >> tmp;
            debugMod = 2;
            if(tmp[0] == 'f' || tmp[0] == 'l'){
                debugCount = label_table[tmp];
            }
            else{
                debugCount = stoul(tmp);
            }
            return;
        }
        if(tmp == "r"){
            //Run
            debugMod = false;
            return;
        }
    }
}
void debugFunc(unsigned long pc, unordered_map<int, int> & lo_symbol){
    //debugMod: 1. run n step
    //          2. run until pc equal debugCount
    if(debugMod == 1){
        if(debugCount)
            debugCount --;
        else{
            intoDebug(pc, lo_symbol);
            if(debugMod == 1)
                debugCount--;
            return;
        }
    }
    else if(debugMod == 2){
        if(debugCount == pc){
            intoDebug(pc, lo_symbol);
        }
    }
}
