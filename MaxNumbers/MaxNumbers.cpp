#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <algorithm>
#include <vector>

/*
* Find the k max elements on an array of size n.
* Implement using heap.
*/

int const MAXN = 10;
int const MAXV = 100;

int arr[MAXN];
int n, k;

int main()
{
    // generate a random array to test
    srand((unsigned)std::time(0));
    n = rand() % MAXN + 1;

    k = rand() % (n - 1) + 1;

    std::cout << "n = " << n << ", k = " << k << std::endl;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % MAXV + 1;

        std::cout << arr[i] << ", ";
    }

    std::cout << std::endl;

    // find the first k max values
     
    // construct heap of size k from array
    std::vector<int> heap(arr, arr + k);
    std::make_heap(heap.begin(), heap.end(), std::greater<int>());

    // for the rest of the elements, replace root node if greater than it
    for (int i = k; i < n; i++)
    {
        if (arr[i] > heap[0])
        {
            std::pop_heap(heap.begin(), heap.end());
            heap.pop_back();
            heap.push_back(arr[i]);
            std::push_heap(heap.begin(), heap.end());
        }
    }

    for (int i = 0; i < k; i++)
    {
        std::cout << heap[i] << ", ";
    }
}