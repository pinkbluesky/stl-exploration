#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

std::ofstream fout("cereal.out");
std::ifstream fin("cereal.in");


int n, m;
const int MAXN = 100000;
const int MAXM = 100000;

int c1[MAXM];
int c2[MAXM];

// store cereal
std::unordered_set<int> boxes;

void sol1()
{

	// remove i cows and find answer
	for (int i = 0; i < n; i++)
	{
		int count = 0;

		// for each cow
		for (int j = i; j < n; j++)
		{
			int first = c1[j];
			int second = c2[j];
			if (boxes.find(first) == boxes.end())
			{
				boxes.insert(first);
				count++;
			}
			else if (boxes.find(second) == boxes.end())
			{
				boxes.insert(second);
				count++;
			}
		}

		boxes.clear();

		fout << count << std::endl;
	}
}

int answer[MAXN];

// cereal box is index, maps to cow id
int taken[MAXM];

void sol2()
{
	int count = 0;


	// remove i cows and find answer
	for (int i = n-1; i >= 0; i--)
	{
		int first = c1[i];
		int second = c2[i];
		
		int j = i;
		int cj = first;

		while (1)
		{
			// if cereal not taken
			if (taken[cj] == 0)
			{
				taken[cj] = j;
				count++;
				break;
			}
			// cereal taken by earlier cow
			else if (taken[cj] < j)
			{
				break;
			}
			// cereal taken by a later cow
			else
			{
				// j2 = the later cow
				int j2 = taken[cj];

				// reassign the cereal to the earlier cow
				taken[cj] = j;

				j = j2;
				
				if (cj == c2[j2])
				{
					break;
				}
				else
				{
					// was j2's first choice
					cj = c2[j2];
				}

			}
		}
		/*
		if (taken[first] != 0)
		{
			// cereal already taken by cowj
			int cowj = taken[first];
			int cerealj = first;

			while (1)
			{
				// j's first selection
				if (c1[cowj] == cerealj)
				{
					// check cowj's second selection
					if (taken[c2[cowj]] == 0)
					{
						// second selection available
						count++;
						taken[c2[cowj]] = cowj;
						break;
					}
					else
					{
						cerealj = c2[cowj];

						// second selection is taken
						// by earlier cow
						if (taken[cerealj] < cowj)
						{
							break;
						}
						// by later cow
						else
						{
							taken[cowj] = cerealj;
							cowj = taken[cerealj];

						}
					}

				}
				else
				{
					// j's second selection
					break;
				}
			}
		}
		else
		{
			count++;
		}
		taken[first] = i;

		*/
		answer[i] = count;

	}

	for (int i = 0; i < n; i++)
	{
		fout << answer[i] << std::endl;
	}
}

int main()
{
	fin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		fin >> c1[i] >> c2[i];
	}
	
	sol2();

	return 0;
}
