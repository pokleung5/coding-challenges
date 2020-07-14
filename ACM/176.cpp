/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 82982
 * Submitted at:  2019-04-24 17:33:34
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    176
 * Problem Name:  Internet Bandwidth (UVa 820)
 */

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>
#include <tuple>

#define maxSize 105
#define _scanf scanf

struct Dinic
{
	int V;

	std::vector<int> graph[maxSize];
	int cap[maxSize][maxSize];
	int level[maxSize];

	bool isConnected(int src, int t)
	{
		memset(level, -1, V * sizeof(int));
		level[src] = 0;

		std::queue<int> q;
		q.emplace(src);

		int u, gap;
		while (q.size())
		{
			u = q.front();
			for (int next : graph[u])
			{
				gap = cap[u][next];
				if (level[next] == -1 && gap > 0)
				{
					level[next] = level[u] + 1;
					q.emplace(next);
				}
			}
			q.pop();
		}
		return level[t] != -1;
	}

	int sendFlow(int u, int t, int flow)
	{
		if (u == t)
			return flow;

		int gap;

		for (int next : graph[u])
		{
			gap = cap[u][next];

			if (level[next] == level[u] + 1 && gap > 0)
			{
				int curr_flow = sendFlow(next, t, std::min(flow, gap));

				if (curr_flow > 0)
				{
					cap[u][next] -= curr_flow;
					cap[next][u] += curr_flow;

					return curr_flow;
				}
			}
		}

		return 0;
	}

	int run(int src, int t)
	{
		if (src == t)
			return 0;

		int total = 0, flow;

		while (isConnected(src, t) == true)
		{
			while (flow = sendFlow(src, t, INT_MAX))
				total += flow;
		}

		return total;
	}

	void addEdge(int u, int v, int C)
	{
		cap[u][v] += C;
		cap[v][u] -= C;

		graph[u].push_back(v);
	}
};

typedef std::pair<int, int> State;
struct FordFulkerson
{
	int V;

	std::vector<int> graph[maxSize];
	int cap[maxSize][maxSize];
	int parent[maxSize];

	int isConnected(int src, int t)
	{
		memset(parent, -1, V * sizeof(int));

		std::queue<State> q;

		for (int next : graph[src])
		{
			if (cap[src][next] > 0) {
				parent[next] = src;
				q.emplace(next, cap[src][next]);
			}
		}

		int u = src, minCap;
		while (q.size() && u != t)
		{
			u = q.front().first;
			minCap = q.front().second;

			for (int next : graph[u])
			{
				if (parent[next] == -1 && cap[u][next] > 0)
				{
					parent[next] = u;
					q.emplace(next, std::min(minCap, cap[u][next]));
				}
			}
			q.pop();
		}

		return parent[t] != -1 ? minCap : 0;
	}

	int run(int src, int t)
	{
		int max_flow = 0;
		int u, v, path_flow;

		while (path_flow = isConnected(src, t))
		{
			for (v = t; v != src; v = parent[v])
			{
				u = parent[v];
				cap[u][v] -= path_flow;
				cap[v][u] += path_flow;
			}

			max_flow += path_flow;
		}

		return max_flow;
	}

};


void addEdge(FordFulkerson& f, int u, int v, int C)
{
	f.cap[u][v] += C;
	f.cap[v][u] += C;

	f.graph[u].push_back(v);
	f.graph[v].push_back(u);
}

int main() 
{
	FordFulkerson f;

	int u, v, w;
	int maxFlow;
	int counter = 1;
	int from, to, E;


	while (_scanf("%d", &f.V) != EOF && f.V != 0)
	{
		++f.V;
		memset(f.cap, 0, sizeof(f.cap));
		// from 1 to N
		_scanf("%d%d%d", &from, &to, &E);

		for (int i = 0; i < E; ++i)
		{
			_scanf("%d%d%d", &u, &v, &w);
			addEdge(f, u, v, w);
		}

		printf("Network %d\nThe bandwidth is %d.\n\n", counter++, f.run(from, to));
	}

	return 0;
}