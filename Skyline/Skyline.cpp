#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings) {

    // pair: x-coord, height (pos if start, neg if end)
    std::vector<std::pair<int, int>> bx;
    // process building data
    // store left and right-coords of buildings, and sort by x-val
    for (auto building : buildings)
    {
        bx.push_back(std::make_pair(building[0], -building[2]));
        bx.push_back(std::make_pair(building[1], building[2]));
    }

    // sort by x-val
    std::sort(bx.begin(), bx.end());


    // store current valid heights
    std::multiset<int> skyline;

    std::vector<std::vector<int>> res;

    int prev = 0;

    skyline.insert(0);

    // for each start/endpoint
    for (auto b : bx)
    {

        // store previous skyline value
        int temp = -1;
        if (skyline.size())
        {
            temp = *skyline.rbegin();
        }

        // if we are at the end of this building
        if (b.second > 0)
        {
            // erase this height from skyline
            // skyline.erase(b.second);

            auto itr = skyline.find(b.second);
            if (itr != skyline.end()) {
                skyline.erase(itr);
            }

        }

        // we are at the start of this building
        if (b.second < 0)
        {
            // add to multiset
            skyline.insert(-b.second);
        }

        // if new skyline value, add to result (or if the 1st skyline val)
        if ((skyline.size()  && *skyline.rbegin() != prev))
        {       
            res.push_back({ b.first, *skyline.rbegin() });

            prev = *skyline.rbegin();
        }
        /*
        // if at the end of this building 
        if (b.second < 0 && !skyline.size())
        {
            // and there's no buildings on the skyline
            res.push_back({ b.first, 0 });
        }*/
    }

    return res;
}

int main()
{
    std::vector<std::vector<int>> buildings = { {2, 9, 10} ,{3, 7, 15}, {5, 12, 12},{15, 20, 10},{19, 24, 8} };
    // Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]

    std::vector<std::vector<int>> res = getSkyline(buildings);

    std::cout << "buildings 1" << std::endl;
    for (auto v1 : res)
    {
            std::cout << v1[0] << ", " << v1[1] << std::endl;
    }


    std::vector<std::vector<int>> buildings2 = { {0, 2, 3}, {2, 5, 3} };
    // Output: [[0, 3], [5, 0]]

    res = getSkyline(buildings2);
    std::cout << "buildings 2" << std::endl;
    for (auto v1 : res)
    {
        std::cout << v1[0] << ", " << v1[1] << std::endl;
    }


}
