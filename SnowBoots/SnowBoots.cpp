#include <fstream>

int n, b;

const int MAX = 100000;

int path[MAX];

struct pair {
    int depth;
    int step;
};

pair boots[MAX];

std::ofstream fout("snowboots.out");
std::ifstream fin("snowboots.in");

int main()
{
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

        // iterate through and find differences in step size (for the tiles where the boots can step)
        int prev_j = 0;
        for (int j = 0; j < n; j++)
        {
            if (path[j] <= boots[i].depth)
            {
                // if the step is too great
                if (j - prev_j > boots[i].step)
                {
                    is_possible = false;
                    break;
                }
                prev_j = j;
            }
        }
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