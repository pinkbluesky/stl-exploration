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

// cereal value maps to cow id
std::unordered_map<int, int> map;
int answer[MAXN];

// returns the number of cows that can't take cereal anymore
int remove(int cereal)
{
	int res = 0;
	// if we must rearrange
	if (map.find(cereal) != map.end())
	{

		int affected_cow = map[cereal];

		// if we need to remove a cow's first selection
		if (cereal == c1[affected_cow])
		{
			if (map.find(c2[affected_cow]) == map.end())
			{
				map.erase(cereal);
				map[c2[affected_cow]] = affected_cow;
				return 0;
			}
			else
			{
				int res = remove(c2[affected_cow]);
				map.erase(cereal);
				// this cow is unable to take cereal
				return res;
			}
			
		}
		else
		{
			res++;
		}
	}
	return res;
}

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
		
		int cowj = i;
		int cerealj = first; 

		while (1)
		{
			if (taken[cerealj] == 0)
			{
				// not taken
				break;
				taken[cerealj] = cowj;
			}
			else if (taken[cerealj] < cowj)
			{
				// cereal was taken by cow before it
				taken[cerealj] = cowj;
				
				// if it was the cow's first selection
			}
		}

		/*

		// adding this new cow to the sequence

		// if adding this cow doesn't affect things
		if (map.find(first) == map.end())
		{
			count++;
			// actually add it
			map[first] = i;

			answer[i] = count;
		}
		else
		{
			// adding this cow means that some things have to be rearranged
			
			// the cow who has already taken that cereal
			int cowj = map[first];
			int cerealj = first;

			while (1)
			{

				if (cerealj == c1[cowj])
				{
// test
					cerealj = c2[cowj];

					auto it = map.find(c2[cowj]);
					// check the second option for the cow
					if (it == map.end())
					{
						// second is available
						map[c2[cowj]] = cowj;
						// map.erase(c1[cowj]);
						break;
					}
					// if the cow's second option was taken by a previous cow
					else if (it->second < cowj)
					{
						// second option is taken as well
						
						//map.erase(c1[cowj]);
						break;
					}
					else
					{
						// second option taken by a later cow
						map[cerealj] = cowj;

						cowj = it->second;
						cerealj = it->first;
					}
				}
				else
				{
					count--;
					map[cerealj] = cowj;
					
					break;
				}

			}

			count++;
			// actually add it
			map[first] = i;

			//answer[i] = count;
			answer[i] = map.size();
		}*/
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
