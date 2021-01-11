#include <fstream>
#include <set>
#include <algorithm>
#include <map>
#include <vector>

int n, b;

const int MAX = 100000;

std::ofstream fout("snowboots.out");
std::ifstream fin("snowboots.in");


// solution 1
int path[MAX];
struct pair {
    int depth;
    int step;
};

pair boots[MAX];
// depth maps to the greatest difference between valid tiles
std::map<int, int> max_steps;

void sol() {

    // read input
    fin >> n >> b;

    for (int i = 0; i < n; i++)
    {
        fin >> path[i];
    }

    for (int i = 0; i < b; i++)
    {
        int d, s;
        fin >> d >> s;
        boots[i] = { d, s };
    }

    // for each pair of boots
    for (int i = 0; i < b; i++)
    {
        // take the smallest steps possible

        bool is_possible = true;

        if (max_steps.find(boots[i].depth) == max_steps.end())
        {
            // iterate through and find max difference in step size
            int prev_j = 0;
            int max = -1;
            for (int j = 0; j < n; j++)
            {
                // valid tile?
                if (path[j] <= boots[i].depth)
                {
                    max = std::max(max, j - prev_j);
                    /*
                    // if the step is too great
                    if (j - prev_j > boots[i].step)
                    {
                        is_possible = false;
                        break;
                    }
                    */
                    prev_j = j;
                }
            }

            max_steps[boots[i].depth] = max;
        }

        is_possible = (boots[i].step >= max_steps[boots[i].depth]);

        if (is_possible)
        {

            fout << 1 << std::endl;
        }
        else
        {
            fout << 0 << std::endl;
        }

        // if all differences are less than step size, then great!
    }
}



int main()
{
    sol();
}