#include <iostream>
#include <algorithm>
#include <set>

const int MAX = 100005;

int n, q;

struct range {
    int a, b;
};

range ranges[MAX];
char goal[MAX];

char fence[MAX];

// for each color, keep track of which indexes it wants
std::set<int> colors[130];

int count_strokes(int a, int b)
{
    std::set<int> prev_ci;

    bool first = true;

    int strokes = 1;

    for (char i = 'A'; i <= 'Z'; i++)
    {
        std::set<int> ci = colors[i];

        if (ci.size() != 0 && (ci.lower_bound(a) != ci.end() || ci.upper_bound(b) != ci.end()))
        {

            if (first)
            {
                first = false;
                prev_ci = colors[i];
            }

            int max_i = *ci.rbegin();
            int min_i = *ci.begin();

            // the position in the set for the lighter color, and for the darker color
            auto light_i = prev_ci.begin();
            auto dark_i = ci.begin();

            while (*light_i < a)
            {
                ++light_i;
            }
            while (*dark_i < a)
            {
                ++dark_i;
            }
            int prev_i = std::min(*light_i, *dark_i);

            int cur_i = -1;

            while (cur_i <= b)
            {
                // initialize current index
                while (light_i != prev_ci.end() && *light_i < *dark_i)
                {
                    cur_i = *light_i;

                    ++light_i;
                }

                if (light_i == prev_ci.end())
                {
                    break;
                }

                strokes++;

                while (dark_i != ci.end() && *dark_i < *light_i)
                {

                    ++dark_i;
                }

                if (dark_i == ci.end())
                {
                    break;
                }
            }

            prev_ci = ci;
        }
    }
    return strokes;
}

int main()
{
    std::cin >> n >> q;

    for (int i = 0; i < n; i++)
    {
        std::cin >> goal[i];
        colors[goal[i]].insert(i);
    }

    for (int i = 0; i < q; i++)
    {
        std::cin >> ranges[i].a >> ranges[i].b;
    }

    // for each range
    for (int i = 0; i < q; i++)
    {
        std::cout << count_strokes(0, ranges[i].a) + count_strokes(ranges[i].a, ranges[i].b) << std::endl;
    }
}