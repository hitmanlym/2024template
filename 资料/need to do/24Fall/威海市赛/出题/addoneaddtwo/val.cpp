#include "testlib.h"
 
using i64 = long long;
 
const int N = 1e5 + 1, M = 1e9 + 1;
 
int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	
	int testCaseCount = inf.readInt(1, N, "t");
    inf.readEoln();

    for (int testCase = 1; testCase <= testCaseCount; testCase++) {
        setTestCase(testCase);
        int n = inf.readInt(1, N, "n");
        inf.readSpace();
        int x = inf.readInt(0, N, "x");
        inf.readSpace();
        int y = inf.readInt(0, N, "y");
        inf.readEoln();

        for (int i = 1; i <= n; i ++) {
			inf.readInt(0, M, "a_i");
			if (i < n) inf.readSpace();
		}
        inf.readEoln();
    }

    inf.readEof();
	return 0;
}
