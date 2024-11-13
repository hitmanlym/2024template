#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    
    int test_count = opt<int>("test-count");
    int sum_n = opt<int>("sum-n");
    int min_n = opt<int>("min-n", 1);
    
    int min_value = opt<int>("min-value", 1);
    int max_value = opt<int>("max-value", 1000 * 1000 * 1000);
    int value_bias = opt<int>("value-bias", 0);
    
    std::vector<int> n_list = rnd.partition(test_count, sum_n, min_n);
    
    println(test_count);
    for (int test_case = 0; test_case < test_count; ++test_case) {
        int n = n_list[test_case];
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = rnd.wnext(min_value, max_value, value_bias);
        }
        println(n);
        println(arr);
    }
}