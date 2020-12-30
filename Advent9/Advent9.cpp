#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <time.h>

// https://adventofcode.com/2020/day/9

std::ifstream fin("a9.in");
std::ofstream fout("a9.out");

const int MAXN = 1000000;
const int N = 25;

int arr[MAXN];

// store every sum here: sum points to a pair of indicies that are valid
//std::unordered_set<int> sums;

// finds the first non-sum element and returns it
int find_non_sum(int n)
{
	for (int i = N; i < n; i++)
	{
		bool is_sum = false;
		for (int j = i - N; j < i; j++)
		{
			for (int k = j; k < i; k++)
			{
				if (arr[i] == arr[j] + arr[k])
				{
					is_sum = true;
				}
			}
		}

		if (!is_sum)
		{
			return arr[i];
		}
	}

	return 0;
}

// adds the min/max of the sequence of numbers that sum to the invalid number
std::pair<int, int> find_range_of_sum(int val, int n)
{
	std::vector<int> seq_sums;
	
	for (int i = 1; i < n; i++)
	{
		seq_sums.push_back(arr[i - 1]);

		// add constant and cmp
		for (int j = 0; j < seq_sums.size(); j++)
		{
			seq_sums[j] += arr[i];
			if (seq_sums[j] == val)
			{
				// find min/max
				int min = *std::min_element(std::begin(arr) + j, std::begin(arr) + i + 1);
				int max = *std::max_element(std::begin(arr) + j, std::begin(arr) + i + 1);

				return std::make_pair(min, max);

			}
		}
	}

	return std::make_pair(0, 0);
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

	int part1 = find_non_sum(i);

	fout << "Time taken: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << std::endl;

	if (part1)
	{
		fout << part1 << std::endl;
	}
	else
	{
		fout << "nothing for pt1" << std::endl;
	}

	std::pair<int, int> part2 = find_range_of_sum(part1, i);

	fout << part2.first + part2.second << std::endl;

	return 0;
}