#include <fstream>
#include <set>
#include <algorithm>
#include <map>
#include <vector>

int n, b;

const int MAX = 100000;

std::ofstream fout("snowboots.out");
std::ifstream fin("snowboots.in");


// solution 2
std::vector<std::pair<int, int>> pairs;
std::map<int, std::set<int>> tiles;
int result[MAX];


bool compareFunc(int a, int b)
{
    return pairs[a] < pairs[b];
}

void sol() {

    // read input
    fin >> n >> b;

    for (int i = 0; i < n; i++)
    {
        // insert the tile index into tiles map
        int t;
        fin >> t;
        tiles[t].insert(i);
    }

    std::vector<int> pairs_i;

    for (int i = 0; i < b; i++)
    {
        int d, s;
        fin >> d >> s;
        pairs.push_back(std::make_pair(d, s));
        pairs_i.push_back(i);
    }

    // sort pairs by depth then step size (ascending)
    std::sort(pairs_i.begin(), pairs_i.end(), compareFunc);
    std::sort(pairs.begin(), pairs.end());

    std::set<int> valid_tiles;

    int prev_depth = -1;
    int max_step = -1;

    // iterate thru the sorted set of boots
    for (int i = 0; i < pairs.size(); i++)
    {
        std::pair<int, int> boot = pairs[i];

        bool is_new_set = false;
        // if uninitialized (first iteration)
        if (prev_depth < 0)
        {
            is_new_set = true;
            valid_tiles = tiles[boot.first];
        }
        else
        {
            // if new depth, merge new valid tiles
            if (boot.first != prev_depth)
            {
                is_new_set = true;

                std::set<int> temp;

                // merge all valid tiles with depth <= current boot depth
                for (int j = prev_depth + 1; j <= boot.first; j++)
                {
                    if (tiles.find(j) != tiles.end())
                    {
                        /*std::set_union(std::begin(valid_tiles), std::end(valid_tiles),
                            std::begin(tiles[j]), std::end(tiles[j]),
                            std::inserter(temp, std::begin(temp)));*/
                        valid_tiles.insert(tiles[j].begin(), tiles[j].end());
                    }
                }

                //valid_tiles = temp;
            }
        }

        if (is_new_set)
        {
            // now we have a new set of valid tiles
            // find greatest difference within the set
            max_step = -1;
            int prev_tile = -1;
            for (auto t : valid_tiles)
            {
                if (prev_tile < 0)
                {
                    prev_tile = t;
                }
                else
                {
                    max_step = std::max(max_step, t - prev_tile);
                    prev_tile = t;
                }
            }
        }

        // now cmp with max step
        if (boot.second >= max_step)
        {
            // yay! these boots are good
            result[pairs_i[i]] = 1;
            // fout << "1";
        }
        else
        {
            result[pairs_i[i]] = 0;
            // fout << "0";
        }

        //fout << std::endl;

        prev_depth = boot.first;
    }

    // output to file
    for (int i = 0; i < b; i++)
    {
        fout << result[i] << std::endl;
    }
}

int main()
{
    sol();
}