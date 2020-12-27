#include <iostream>
#include <fstream>
#include <queue>
#include <functional>

// http://www.usaco.org/index.php?page=viewproblem2&cpid=859

struct cow {
    int senority;
    int arrival;
    int duration;

    bool operator<(const cow& other) const
    {
        return arrival < other.arrival;
    }
};

struct CompByArrival
{
bool operator()(const cow& c1, const cow& c2) const
{
    return c1.arrival > c2.arrival;
}
};

struct CompBySen
{
    bool operator()(const cow& c1, const cow& c2) const
    {
        return c1.senority > c2.senority;
    }
};

std::ofstream fout("convention2.out");
std::ifstream fin("convention2.in");

// original queue, sorted by arrival time
std::priority_queue<cow, std::vector<cow>, CompByArrival> cows;

// cow queue at any time
std::priority_queue<cow, std::vector<cow>, CompBySen> queue;

int n;

int main()
{
    fin >> n;

    // add cows to queue
    for (int i = 0; i < n; i++)
    {
        int a, d;
        fin >> a >> d;

        cows.push({ i, a, d });
    }

    int max_wait = 0;
    int time = cows.top().arrival;

    // for each cow...
    for (int i = 0; i < n; i++)
    {
        // if the next cows are waiting
        while (cows.size() && cows.top().arrival <= time)
        {
            // add to queue
            queue.push(cows.top());
            cows.pop();
        }

        // if no cow is in queue
        if (queue.size())
        {

            // next cow in queue should eat grass
            // track max wait time
            max_wait = std::max(max_wait, time - queue.top().arrival);
            time += queue.top().duration;
            queue.pop();
        }
        else
        {
            // set time to cows.top().arrival]
            if (cows.size())
            {
                time = cows.top().arrival;
            }
        }
    }

    fout << max_wait << std::endl;
}