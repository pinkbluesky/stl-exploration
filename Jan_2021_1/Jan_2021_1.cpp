#include <iostream>
#include <algorithm>

#include <unordered_map>
#include <set>

const int MAXN = 100005;
const int MAXK = 200005;

int n, k;

int orig_pos[MAXN];

// cow id maps to the set of unique positions
std::unordered_map<int, std::set<int>> pos;

std::pair<int, int> static_pos[MAXK];
int static_unique[MAXN];

struct move {
    int a, b;
};

move moves[MAXK];

int main()
{
    std::cin >> n >> k;

    for (int i = 0; i <= n; i++)
    {
        orig_pos[i] = i;
        pos[i].insert(i);
    }

    for (int i = 0; i < k; i++)
    {
        std::cin >> moves[i].a >> moves[i].b;
    }

    // foreach dance move
    for (int i1 = 0; i1 < 185; i1++)
    {
        for (int i = 0; i < k && moves[i].a > 0; i++)
        {
            int a = moves[i].a;
            int b = moves[i].b;

            if (static_pos[i] == std::make_pair(orig_pos[a], orig_pos[b]))
            {
                moves[i].a = -1;
                moves[i].b = -1;
                continue;
            }

            static_pos[i] = std::make_pair(orig_pos[a], orig_pos[b]);

            static_unique[orig_pos[a]] = pos[orig_pos[a]].size();
            static_unique[orig_pos[b]] = pos[orig_pos[b]].size();

            // swap
            pos[orig_pos[a]].insert(b);
            pos[orig_pos[b]].insert(a);

            int temp = orig_pos[a];
            orig_pos[a] = orig_pos[b];
            orig_pos[b] = temp;
            /*
            if (static_unique[orig_pos[a]] == pos[orig_pos[a]].size() && static_unique[orig_pos[b]] == pos[orig_pos[b]].size())
            {
                moves[i].a = -1;
                moves[i].b = -1;
                continue;
            }
            */

        }
    }
    for (int i = 1; i <= n; i++)
    {
        std::cout << pos[i].size() << std::endl;
    }

    return 0;
}