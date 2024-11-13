#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int length = opt<int>(1);
    println(rnd.next("[a-z]{1,%d}", length));
}