#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <time.h>

// https://adventofcode.com/2020/day/9
// optimizing Advent Day 9

std::ifstream fin("a9.in");
std::ofstream fout("a9.out");

const int MAXN = 1000;
const int N = 25;

int arr[MAXN];

// key = sum, value = count
std::unordered_map<int, int> sums;

// optimize by using unordered_map
// O(nk)
int find_non_sum(int len)
{
	for (int i = 0; i < len; i++)
	{
		// if preamble:
		if (i < N)
		{
			for (int j = 0; j < i; j++)
			{
				sums[arr[i] + arr[j]]++;
			}
		}	
		// if not preamble:
		else
		{
			// decrement for sums involving arr[i - N - 1]
			int index_to_erase = i - N - 1;
			for (int j = index_to_erase + 1; j < i; j++)
			{
				sums[arr[j] + arr[index_to_erase]]--;
			}

			// lookup
			if (sums.find(arr[i]) == sums.end())
			{
				return arr[i];
			}

			// increment
			for (int j = i - N; j < i; j++)
			{
				sums[arr[j] + arr[i]]++;
			}
		}
	}
	return 0;
}

int main()
{
	clock_t tStart = clock();

	int i = 0;
	while (i < MAXN && !fin.eof())
	{
		fin >> arr[i];
		i++;
	}

	fout << find_non_sum(i) << std::endl;

	fout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << std::endl;
	return 0;

}
