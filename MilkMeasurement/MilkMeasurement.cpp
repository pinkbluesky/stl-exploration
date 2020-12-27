#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

int n, g;

const int MAXN = 1000005;

std::ofstream fout("measurement.out");
std::ifstream fin("measurement.in");

struct measurement {
    int day;
    int cow;
    int gal;
};

int main()
{
    fin >> n >> g;

    // key => cow id, value => gallons produced
    std::map<int, int> cows;


    std::vector<measurement> g_log(n);

    // record g_log
    for (auto& m : g_log)
    {
        fin >> m.day >> m.cow >> m.gal;

        // insert value into cows set
        cows[m.cow] = g;

    }

    // sort log by day
    std::sort(g_log.begin(), g_log.end(), [](const measurement& a, const measurement& b) { return a.day < b.day; });

    int result = 0;

    // map with max gallons as key, and # of occurences as value
    std::map<int, int, std::greater<int>> cows_count;

    // initialize cows_count by default
    cows_count[0] = -1;

    // for each day...
    for (auto m : g_log)
    {
        int cur_cow_id = m.cow;

        int orig_gal = cows[cur_cow_id];

        // first, check if cow id WAS a top cow
        int was_top = orig_gal == cows_count.begin()->first; // does gal equal the top gal?

        // remove/update the cow count
        if (cows_count[orig_gal] == 1 || cows_count[orig_gal] == 0)
        {
            cows_count.erase(orig_gal);
        }
        else
        {
            cows_count[orig_gal]--;
        }

        // track the top cow count
        int orig_top_count = cows_count.begin()->second;

        // update this cow's gallons
        cows[cur_cow_id] += m.gal;

        int new_gal = cows[cur_cow_id];

        // update the cow count for the new gallons value
        if (cows_count.count(new_gal) == 1)
        {
            cows_count[new_gal]++;
        }
        else
        {
            cows_count[new_gal] = 1;
        }

        // now, check if this cow IS a top cow
        int is_top = cows[cur_cow_id] == cows_count.begin()->first;

        // track if top cow count has changed
        int top_count_changed = orig_top_count - cows_count.begin()->second;

        // conditions to figure out if Farmer John needs to update display
        if (was_top)
        {
            // if was top cow

            // if no longer a top cow
            if (!is_top || top_count_changed)
            {
                result++;
            }
        }
        else
        {
            // if wasn't a top cow

            // if is a top cow now
            if (is_top)
            {
                result++;
            }
        }
    }

    fout << result << std::endl;
}