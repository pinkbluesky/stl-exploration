#include <fstream>
#include <algorithm>
#include <vector>

int n, b;

const int MAXN = 100000;
const int MAXB = 100000;

// holds master array of tiles
int tiles[MAXN];
int tid[MAXN];
// doubly linked list - the next valid tiles
int next[MAXN];
// doubly linked list - the previous valid tiles
int prev[MAXN];
// ^ rather than do set unions lollolol aiya

// boots; sorted by depth then step size
std::vector<std::pair<int, int>> boots;
// "sorted" boot ids (so we can output result correctly)
std::vector<int> bid;

int result[MAXB];


bool compareFuncBid(int a, int b)
{
	return boots[a] < boots[b];
}

bool compareFuncTid(int a, int b)
{
	return tiles[a] < tiles[b];
}

std::ofstream fout("snowboots.out");
std::ifstream fin("snowboots.in");

int main()
{
	fin >> n >> b;
	
	// read tiles input
	for (int i = 0; i < n; i++)
	{
		fin >> tiles[i];

		next[i] = i + 1;
		prev[i] = i - 1;

		tid[i] = i;
	}

	// read boots input
	for (int i = 0; i < b; i++)
	{
		int d, s;
		fin >> d >> s;
		boots.push_back(std::make_pair(d, s));
		bid.push_back(i);
	}

	// sort boots in descending depth order
	std::sort(bid.begin(), bid.end(), compareFuncBid);
	std::sort(boots.begin(), boots.end());

	std::sort(tid, tid + n, compareFuncTid);

	// track the largest valid tile
	int j = n - 1;

	// process 
	int max = -1;
	for (int i = b-1; i >= 0; i--)
	{
		std::pair<int, int> boot = boots[i];

		// find the max step

		// for each invalid tile
		while (j >= 0 && tiles[tid[j]] > boot.first)
		{
			int cur_tile_id = tid[j];
			prev[next[cur_tile_id]] = prev[cur_tile_id];
			next[prev[cur_tile_id]] = next[cur_tile_id];

			max = std::max(max, next[cur_tile_id] - prev[cur_tile_id]);
			j--;
		}
		/*
		for (int j = 0; j < n; j++)
		{
			if (tiles[j] > boot.first)
			{
				// remove from tiles linked list
				prev[next[j]] = prev[j];
				next[prev[j]] = next[j];

				if (prev[j] >= 0 && next[j] < n)
				{
					max = std::max(max, next[j] - prev[j]);
				}
			}
		}
		*/
		result[bid[i]] = (boot.second >= max ? 1 : 0);
	}

	// output result
	for (int i = 0; i < b; i++)
	{
		fout << result[i] << std::endl;
	}
}