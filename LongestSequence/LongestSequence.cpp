#include <iostream>
#include <ctime> 
#include <vector>
#include <algorithm>

/***
* Given an array of integers, find the length of the longest increasing subsequence, from left to right.
* Sequence doesn't have to be continuous.
*/

int const MAXN = 10;
int const MAXV = 100;

int arr[MAXN];
int n;

int main()
{
    // generate random array and print it out
    srand((unsigned)std::time(0));
    n = rand() % MAXN + 1;

    std::cout << "n = " << n << std::endl;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % MAXV + 1;

        std::cout << arr[i] << ", ";
    }

    std::cout << std::endl;

    
    // find the longest increasing sequence
    std::vector<int> sequences;

    // binary search
    int cur_seq = 0;
    for (int i = 0; i < n; i++)
    {
        auto it = std::upper_bound(sequences.begin(), sequences.end(), arr[i]);

        // replace this value
        if (it != sequences.end())
        {
            *it = arr[i];
        }
        // append to vector
        else
        {
            sequences.push_back(arr[i]);
        }
    }

    std::cout << "Length of longest sequence: " << sequences.size() << std::endl;
}
