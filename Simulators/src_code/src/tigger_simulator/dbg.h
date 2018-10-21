#ifndef DBG_H
#define DBG_H

#include <set>

extern bool debug;
extern int run_type;
#define DEBUG_NEXT 1
#define DEBUG_CONTINUE 2

extern std::set<int> breaks;
void debug_wait();

#endif //DBG_H
