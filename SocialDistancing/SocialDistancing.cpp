
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

/*
* Notes: sort intervals, use greedy algorithm to check d's while binary searching d's
*/

typedef unsigned long long bigint;

std::ofstream fout("socdist.out");
std::ifstream fin("socdist.in");

int n, m;
std::vector<std::pair<bigint, bigint>> intervals;

bool test_d(bigint d)
{
	bigint min_range = intervals[0].first;
	bigint prev = min_range;
	int prev_i = 0;
	// for each cow
	for (int i = 1; i < n; i++)
	{
		// place it in the leftmost position
		bigint next = prev + d;
		// find the next interval 
		int cur_i = prev_i;
		while (cur_i < intervals.size() && next <= intervals[intervals.size() - 1].second)
		{
			// if next val is less than current interval
			if (next < intervals[cur_i].first)
			{
				next = intervals[cur_i].first;
			}
			// if next val is within current interval
			else if (next >= intervals[cur_i].first && next <= intervals[cur_i].second)
			{
				prev = next;
				prev_i = cur_i;
				break;
			}
			// if next val is greater than current interval
			else
			{
				cur_i++;
			}
		}

		// if cow couldn't be placed
		if (cur_i >= intervals.size() || next > intervals[intervals.size() - 1].second)
		{
			return false;
		}
	}

	return true;
}

int main()
{
	fin >> n >> m;

	// read input
	for (int i = 0; i < m; i++)
	{
		bigint a, b;
		fin >> a >> b;
		intervals.push_back(std::make_pair(a, b));
	}

	// sort by left point
	std::sort(intervals.begin(), intervals.end());


	bigint min_range = intervals[0].first;
	bigint max_range = intervals[intervals.size() - 1].second;

	bigint temp = 1;

	bigint min_d = 1;
	bigint max_d = max_range - min_range;

	bigint res = -1;

	// binary search d
	while (max_d >= min_d)
	{
		bigint mid = (max_d + min_d) / 2;
		bool valid = test_d(mid);

		// if d works
		if (valid)
		{
			res = mid;
			// update range
			min_d = mid + 1;
		}
		else
		{
			// update range
			max_d = mid - 1;
		}
	}

	fout << res << std::endl;
}
