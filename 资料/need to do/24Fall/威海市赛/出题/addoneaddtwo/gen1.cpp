#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    
    int test_count = opt<int>(1);
    int sum_n = opt<int>(2);
    int min_n = opt<int>("min-n", 1);
    
    int min_value = opt<int>("min-value", 0);
    int max_value = opt<int>("max-value", 1000 * 1000 * 1000);
    int value_bias = opt<int>("value-bias", 0);
    
    std::vector<int> n_list = rnd.partition(test_count, sum_n, min_n);
    
    //println(test_count);
    printf("%d\n", test_count);
    for (int test_case = 0; test_case < test_count; ++test_case) {
        int n = n_list[test_case];
        if (n % 2 == 0) n ++;
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = rnd.wnext(min_value, max_value, value_bias);
        }
        int x = rnd.next(0, N);
        int y = rnd.next(0, N);
        printf("%d %d %d\n", n, x, y);
        for (int i = 0; i < n; i ++) {
            printf("%d", arr[i]);
            if (i + 1 < n) printf(" ");
        }
        printf("\n");
    }
}