#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

// http://www.usaco.org/index.php?page=viewproblem2&cpid=743

int n;

const int MAXN = 100001;

// stores the paint layering sequence
std::vector<int> stack;

// stores intervals - min and max for each color
int minc[MAXN], maxc[MAXN], painting[MAXN];

std::ofstream fout("art2.out");
std::ifstream fin("art2.in");

int main()
{
    fin >> n;

    int result = 0;

    std::fill(minc, minc + MAXN, MAXN);
    std::fill(maxc, maxc + MAXN, -1);

    // read input and store in painting
    // store intervals
    for (int i = 0; i < n; i++)
    {
        int color; fin >> color;
        painting[i] = color;
        minc[color] = std::min(i, minc[color]);
        maxc[color] = std::max(i, maxc[color]);
    }

    // iterate through painting
    for (int i = 0; i < n; i++)
    {
        int color = painting[i];

        // continue if color is not 0
        if (color)
        {
            // if beginning of interval
            if (i == minc[color])
            {
                // push onto stack
                stack.push_back(color);
                // update result with new depth if applicable
                result = std::max(result, (int)stack.size());
            }

            // if invalid color that isn't on the stack (should have been pushed on previously, or revealed when subinterval popped off)
            if (color != stack[stack.size() - 1])
            {
                result = -1;
                break;
            }

            // if end of interval
            if (i == maxc[color])
            {
                // pop off stack
                stack.pop_back();
            }
        }
    }

    fout << result << std::endl;
}
