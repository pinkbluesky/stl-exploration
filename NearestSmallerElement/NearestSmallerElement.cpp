#include <iostream>
#include <stack>
#include <string>

// https://cses.fi/problemset/task/1645

/*
Given an array, $a$, of $N$ ($1 \le N \le 10^5$) integers, for every index $i$, find the rightmost index $j$ such that $j < i$ and $a_i > a_j$.
*/
int main()
{
    int n;
    std::cin >> n;

    // stack of (index, number) pairs
    std::stack<std::pair<int, int>> arr;

    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        arr.push(std::make_pair(i, x));
    }

    std::string result = "";

    for (int i = 0; i < n; i++)
    {
        std::pair<int, int> a_i = arr.top();
        std::stack<std::pair<int, int>> copy = arr;

        int x = 0;
        // while next value is not less than a_i
        while (copy.size() && a_i.second <= copy.top().second)
        {
            copy.pop();
        }

        if (copy.size())
        {
            x = copy.top().first + 1;
        }

        result = std::to_string(x) + " " + result;
        arr.pop();
    }
    /*
    std::pair<int, int> prev = arr.top();
    for (int i = 0; i < n; i++)
    {
        int min_pos = 0;
        std::stack<std::pair<int, int>> copy = arr;

        // pop i values.
        for (int j = 0; j < i; j++)
        {
            // store if smaller than value at index i.
            if (copy.top().second < prev.second)
            {
                min_pos = copy.top().first;
                copy.pop();
            }
        }

        prev = arr.top();

        std::cout << min_pos << " ";

    }*/

    std::cout << result << "\n";
}