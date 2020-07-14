/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 85790
 * Submitted at:  2019-05-06 19:49:44
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    378
 * Problem Name:  Monster Synthesis
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>
#include <stack>
#define _vardump(x) std::cerr << #x << " is " << x << endl;
#define _isDigit(c) (c >= '0' && c <= '9')

#define maxSize 105
#define INF 100000
using namespace std;

int V, M;

vector<int> graph[maxSize];
int dist[maxSize][maxSize];
bool visited[maxSize];
int level[maxSize];

void init()
{
	for (int i = 0; i < V; ++i)
	{
		graph[i].clear();
		memset(dist[i], -1, V * sizeof(int));
	}
}

void addEdge(int u, int v, int w)
{
	graph[u].emplace_back(v);
	dist[u][v] = std::min<unsigned int>(dist[u][v], w);
}

typedef pair<int, int> minMax;
typedef tuple<int, int, minMax> State;
int runDijkstra(int src, int target)
{
	memset(visited, false, V);
	
	priority_queue<State> q;
	q.emplace(0, src, make_pair(INF, 0));

	int t_min, t_max;

	while (q.size())
	{
		minMax t_mm;
		int u, d;
		tie(d, u, t_mm) = q.top();


		if (u == target)
			return -d;
		
		q.pop();

		visited[u] = true;

		for (int v : graph[u])
		{
			if (visited[v] == false && dist[u][v] > 0)
			{
				t_min = min(level[v], t_mm.first);
				t_max = max(level[v], t_mm.second);

				if (t_max - t_min <= M)
					q.emplace(d - dist[u][v], v, make_pair(t_min, t_max));
			}
		}
	}

	return dist[0][target];
}

int main()
{
	int cost, L, nR, v;

	while (scanf("%d %d", &M, &V)!= EOF)
	{
		++V;

		init();

		for (int i = 1; i < V; ++i) {
			scanf("%d %d %d", &cost, &L, &nR);

			addEdge(0, i, cost);
			level[i] = L;

			while (nR--)
			{
				scanf("%d %d", &v, &cost);
				addEdge(v, i, cost);
			}
		}
	
		printf("%d\n", runDijkstra(0, 1));

	}


}
