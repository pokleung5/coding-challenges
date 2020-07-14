/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 80366
 * Submitted at:  2019-03-15 16:48:51
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    375
 * Problem Name:  Making Okonomiyaki
 */


#include <iostream>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <string>
#include <queue>
#include <unordered_map>
#include <limits.h>

#define turn_on_fastIO                     \
	std::ios_base::sync_with_stdio(false); \
	std::cin.tie(NULL);

#define _end '\n'
#define _tab '\t'
#define _scanf scanf
#define INF -INT_MAX

using namespace std;

const int noOfCups = 4;
const int memSize = 4 * sizeof(int);
const int maxVol = 25;
int maxA, maxB, maxC, maxD, T;
int maxOfCup[noOfCups];

struct state
{
	string key;
	unsigned int vol[noOfCups];

	state(int _a, int _b, int _c, int _d)
	{
		vol[0] = _a;
		vol[1] = _b;
		vol[2] = _c;
		vol[3] = _d;
	}

	inline state *_copy()
	{
		return new state(vol[0], vol[1], vol[2], vol[3]);
	}

	inline bool reachedT()
	{
		for (int i = 0; i < noOfCups; ++i)
			if (vol[i] == T)
				return true;
		return false;
	}
};

int BFS()
{
	bool memo[maxVol][maxVol][maxVol][maxVol]{0};

	queue<pair<state *, int>> q;
	state *temp;

	q.push(make_pair(new state(0, 0, 0, 0), 0));

	while (q.empty() == false)
	{
		temp = q.front().first;

		if (memo[temp->vol[0]][temp->vol[1]][temp->vol[2]][temp->vol[3]] == false)
		{
			memo[temp->vol[0]][temp->vol[1]][temp->vol[2]][temp->vol[3]] = true;

			for (int i = 0; i < noOfCups; ++i)
			{
				state *newState = temp->_copy();

				if (newState->vol[i] != maxOfCup[i])
				{
					newState->vol[i] = maxOfCup[i];

					if (newState->reachedT())
						return q.front().second + 1;

					q.emplace(newState, q.front().second + 1);

					newState = temp->_copy();
				}

				if (newState->vol[i] != 0)
				{
					newState->vol[i] = 0;

					if (newState->reachedT())
						return q.front().second + 1;

					q.emplace(newState, q.front().second + 1);
					newState = temp->_copy();

					for (int j = 0; j < noOfCups; ++j)
					{
						if (newState->vol[j] == maxOfCup[j] || i == j)
							continue;

						newState->vol[j] += newState->vol[i];

						if (newState->vol[j] > maxOfCup[j])
						{
							newState->vol[i] = newState->vol[j] - maxOfCup[j];
							newState->vol[j] = maxOfCup[j];
						}
						else
						{
							newState->vol[i] = 0;
						}

						if (newState->reachedT())
							return q.front().second + 1;

						q.emplace(newState, q.front().second + 1);

						newState = temp->_copy();
					}
				}
			}
		}
		q.pop();
		delete temp;
	}
	return -1;
}

int main()
{
	turn_on_fastIO;

	int step;
	while (_scanf("%d %d %d %d %d", &maxOfCup[0], &maxOfCup[1], &maxOfCup[2], &maxOfCup[3], &T) != EOF)
	{
		step = BFS();

		if (step < 1)
			printf("-1\n");
		else
			printf("%d\n", step);
	}
	return 0;
}