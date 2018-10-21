#define iOP2	1
#define iOP1	2
#define iASS	3
#define iARRSET	4
#define iARRGET	5
#define iIF	6
#define iGOTO	7
#define iPARAM	8
#define iCALLVOID	9
#define iCALL 	10
#define iRETURN	11
#define iVAR	12
#define iNOOP	0

#include <string>

//struct ins{
//	int type;
//	std::string arg1, arg2, arg3, arg4;
//	ins() = default;
//	ins(int _type, std::string _arg1 = "", std::string _arg2 = "",
//		std::string _arg3 = "", std::string _arg4 = ""):
//		type(_type), arg1(_arg1), arg2(_arg2), arg3(_arg3) ,arg4(_arg4){}
//};
struct ins{
    int type;
    unsigned arg1, arg2, arg3, arg4;
    ins(int _type = 0 , unsigned  _arg1 = 0, unsigned _arg2 = 0, unsigned _arg3 = 0, unsigned _arg4 = 0):
    type(_type), arg1(_arg1), arg2(_arg2), arg3(_arg3), arg4(_arg4){}
};
struct _store{
    unsigned index;
    std::string label;
    unsigned pos;

    _store(unsigned _index, std::string _label, unsigned _pos):index(_index), label(_label), pos(_pos){}
};
