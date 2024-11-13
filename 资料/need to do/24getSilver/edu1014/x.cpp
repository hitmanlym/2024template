#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 1e7 + 3;
const int MAXM = 1e7 + 3;

int r[MAXN];
int c1[MAXM];
int c2[MAXM];
int sum1[MAXM];
int sum2[MAXM];

signed main() {
    cin.tie(nullptr);
    iostream ::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }
    int now = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        int c = abs(r[i]);
        if (r[i] == 0) {
//            cout << "i:" << i << '\n';
            for (int j = 0; j <= now; j++) {
                sum1[j] = sum1[j - 1] + c1[j];
//                cout << sum1[j] << ' ';
            }
//            cout << '\n';
            for (int j = 0; j <= now; j++) {
                sum2[j] = sum2[j - 1] + c2[j];
//                cout << sum1[j] << ' ';
            }
//            cout << '\n';
            for (int j = 0; j <= now; j++) {
                ans = max(ans, sum1[j] + sum2[now - j]);
            }
            now++;
        }
        else if (r[i] < 0 && now >= -r[i]) {
            c1[c]++;
        } else if (r[i] > 0 && now >= r[i]){
            c2[c]++;
        }
    }
    for (int j = 0; j <= now; j++) {
        sum1[j] = sum1[j - 1] + c1[j];
//        cout << sum1[j] << ' ';
    }
//    cout << '\n';
    for (int j = 0; j <= now; j++) {
        sum2[j] = sum2[j - 1] + c2[j];
//        cout << sum1[j] << ' ';
    }
//    cout << '\n';
    for (int j = 0; j <= now; j++) {
        ans = max(ans, sum1[j] + sum2[now - j]);
    }
    cout << ans << '\n';
    return 0;
}