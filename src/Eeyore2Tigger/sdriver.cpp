#include <cstdlib>

using namespace std;

// Auto-testing
int main() {
	system("minic2eeyore/minic2eeyore < in/in.c > in/in.e");
	system("cp in/in.c minic2eeyore/test_cases/");
	system("cp in/in.e minic2eeyore/test_cases/");
	system("eeyore2mid/eeyore2mid < in/in.e > in/in.m");
	system("cp in/in.c eeyore2mid/test_cases/");
	system("cp in/in.e eeyore2mid/test_cases/");
	system("cp in/in.m eeyore2mid/test_cases/");
	system("mid2tigger/mid2tigger < in/in.m > in/in.t");
	system("cp in/in.c mid2tigger/test_cases/");
	system("cp in/in.e mid2tigger/test_cases/");
	system("cp in/in.m mid2tigger/test_cases/");
	system("cp in/in.t mid2tigger/test_cases/");
}
