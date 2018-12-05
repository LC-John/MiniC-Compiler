#ifndef __COUNT_H__
#define __COUNT_H__

#include "op.h"

class Counter {
    static int paramCount;
    static int tempoCount;
    static int globaCount;

  public:
    static string GenParamCode();
    static string GenTempoCode();
    static string GenGlobaCode();
    static void ParamCountInit();
};

#endif
