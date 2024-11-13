#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

int n, m, k;
void solve()
{
    cin >> n >> m >> k;
    if (k == 1)
    {
        cout << "Yes\n";
        for (int i = 1; i <= n; i++)
            cout << string(m, '*') << '\n';
        return;
    }
    if (k == 2)
    {
        if (n > 1)
        {
            cout << "Yes\n";
            cout << string(m, '*') << '\n';
            for (int i = 1; i < n; i++)
                cout << string(m, '-') << '\n';
        }
        else if (m > 1)
        {
            cout << "Yes\n";
            string tmp = string(m, '-');
            tmp[0] = '*';
            for (int i = 1; i <= n; i++)
                cout << tmp << '\n';
        }
        else
            cout << "No\n";
        return;
    }
    if (k == 3)
    {
        if (n >= 3)
        {
            cout << "Yes\n";
            cout << string(m, '-') << '\n';
            cout << string(m, '*') << '\n';
            for (int i = 1; i <= n - 2; i++)
                cout << string(m, '-') << '\n';
        }
        else if (m >= 3)
        {
            cout << "Yes\n";
            string tmp = string(m, '-');
            tmp[1] = '*';
            for (int i = 1; i <= n; i++)
                cout << tmp << '\n';
        }
        else
            cout << "No\n";
        return;
    }
    if (k == 4)
    {
        if (n == 1 or m == 1)
            cout << "No\n";
        else
        {
            cout << "Yes\n";
            string tmp = string(m, '-');
            tmp[0] = '*';
            cout << tmp << '\n';
            for (int i = 1; i < n; i++)
                cout << string(m, '-') << '\n';
        }
        return;
    }
    if (k == 5)
    {
        if (n == 1 or m == 1 or gcd(n, m) == 1)
            cout << "No\n";
        else
        {
            int d = gcd(n, m);
            int x = n / d, y = m / d;
            cout << "Yes\n";
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                    cout << (i / x == j / y ? '*' : '-');
                cout << '\n';
            }
        }
        return;
    }
    if (k == 6)
    {
        if (m >= 3 and n >= 2)
        {
            cout << "Yes\n";
            string tmp = string(m, '-');
            tmp[1] = '*';
            cout << tmp << '\n';
            for (int i = 1; i < n; i++)
                cout << string(m, '-') << '\n';
        }
        else if (n >= 3 and m >= 2)
        {
            cout << "Yes\n";
            cout << string(m, '-') << '\n';
            string tmp = string(m, '-');
            tmp[0] = '*';
            cout << tmp << '\n';
            for (int i = 1; i <= n - 2; i++)
                cout << string(m, '-') << '\n';
        }
        else
            cout << "No\n";
        return;
    }
    if (k == 7)
    {
        if (n == 1 || m == 1)
        {
            cout << "No\n";
            return;
        }
        if (n <= 2 && m <= 2)
        {
            cout << "No\n";
            return;
        }
        if (n > 2 && m > 2)
        {
            cout << "Yes\n";
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (i == 1 && j >= 2)
                        cout << '*';
                    else if (i == 2 && j == 1)
                        cout << '*';
                    else
                        cout << "-";
                }
                cout << '\n';
            }
            return;
        }
        if (n == 2 || m == 2)
        {
            cout << "Yes\n";
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (i == 1 && j == 2)
                        cout << '*';
                    else if (i == 2 && j == 1)
                        cout << '*';
                    else
                        cout << "-";
                }
                cout << '\n';
            }
            return;
        }
    }
    if (k == 9)
    {
        if (n <= 2 && m <= 2)
        {
            cout << "No\n";
            return;
        }
        if (n == 1 || m == 1)
        {
            cout << "No\n";
            return;
        }
        if (n == 2)
        {
            cout << "Yes\n";
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (i == 1 && j == 3)
                        cout << '*';
                    else if (i == 2 && j == 1)
                        cout << '*';
                    else
                        cout << "-";
                }
                cout << '\n';
            }
            return;
        }
        if (m == 2)
        {
            cout << "Yes\n";
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (j == 1 && i == 3)
                        cout << '*';
                    else if (j == 2 && i == 1)
                        cout << '*';
                    else
                        cout << "-";
                }
                cout << '\n';
            }
            return;
        }
        cout << "Yes\n";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (i == 1 && j == 2)
                    cout << '*';
                else if (i == 2 && j == 1)
                    cout << '*';
                else
                    cout << "-";
            }
            cout << '\n';
        }
        return;
    }
    if (k == 11)
    {
        if (n == 1 || m == 1)
        {
            cout << "No\n";
            return;
        }
        if (n == 2 && m <= 3)
        {
            cout << "No\n";
            return;
        }
        if (m == 2 && n <= 3)
        {
            cout << "No\n";
            return;
        }
        if (n == 2)
        {
            cout << "Yes\n";
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (i == 1 && j == 2)
                        cout << '*';
                    else if (i == 1 && j == 4)
                        cout << '*';
                    else if (i == 2 && j == 1)
                        cout << '*';
                    else
                        cout << "-";
                }
                cout << '\n';
            }
            return;
        }
        if (m == 2)
        {
            cout << "Yes\n";
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (j == 1 && i == 2)
                        cout << '*';
                    else if (j == 1 && i == 4)
                        cout << '*';
                    else if (j == 2 && i == 1)
                        cout << '*';
                    else
                        cout << "-";
                }
                cout << '\n';
            }
            return;
        }
        cout << "Yes\n";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (i == 1 && j == 3)
                    cout << '*';
                else if (i == 2 && j == 1)
                    cout << '*';
                else
                    cout << "-";
            }
            cout << '\n';
        }
        return;
    }
    if (k == 13)
    {
        if (n >= 3 and m >= 3)
        {
            cout << "Yes\n";
            string tmp = string(m, '-');
            tmp[0] = '*';
            cout << tmp << '\n';
            for (int i = 1; i <= n - 2; i++)
                cout << string(m, '-') << '\n';
            tmp[0] = '-', tmp.back() = '*';
            cout << tmp << '\n';
        }
        else
            cout << "No\n";
        return;
    }
    cout << "No\n";
    return;
}
/*
6
1 1 1
2 3 3
9 9 8
2 4 4
3 5 3
2 2 5
*/
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
        solve();
}