#include <iostream>
#include <algorithm>

// https://codeforces.com/contest/702/problem/C

int n, m;

const int MAXN = 100005;

int cities[MAXN], towers[MAXN], min_d[MAXN];

int main()
{
    std::cin >> n;
    std::cin >> m;

    for (int i = 0; i < n; i++)
    {
        std::cin >> cities[i];
    }
    for (int i = 0; i < m; i++)
    {
        std::cin >> towers[i];
    }

    // find the minimum value r such that all cities are covered by the cellular towers

    std::fill(min_d, min_d + MAXN, MAXN);

    // for each city, find the closest cellular tower and distance
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            min_d[i] = std::min(min_d[i], std::abs(towers[j] - cities[i]));
        }
    }

    // find the max of these distances
    std::cout << *std::max_element(min_d, min_d + n) << std::endl;
}