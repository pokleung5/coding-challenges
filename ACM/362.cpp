/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 84525
 * Submitted at:  2019-05-01 16:27:36
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    362
 * Problem Name:  Winger Trial (UVa 11757)
 */

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>
#include <tuple>

#define _scanf scanf
#define maxL 10005
#define maxW 10005
#define maxN 105
#define maxD 10005

#define _scanf scanf
#define INF INT_MAX

const int maxV = 105 * 2;
const int maxE = 105 * 105 * 3;

struct EDGE
{
	int to, prev;
	int c, f;
} edge[maxE];

int S, T, ec; // S connect all 400, T connect all 789;
int head[maxV], level[maxV], curr[maxV];
int xs[maxV], ys[maxV];
int L, W, N, d, sqOf2d;

void addEdge(int u, int v, int cap)
{
	edge[ec].to = v;
	edge[ec].c = cap;
	edge[ec].f = 0;
	edge[ec].prev = head[u];
	head[u] = ec++;

	edge[ec].to = u;
	edge[ec].c = 0;
	edge[ec].f = 0;
	edge[ec].prev = head[v];
	head[v] = ec++;
}

bool Bfs()
{
	memset(level, -1, sizeof(level));

	std::queue<int> q;
	q.push(S);
	level[S] = 0;

	int v;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int e = head[u]; e != -1; e = edge[e].prev)
		{
			v = edge[e].to;
			if (level[v] == -1 && edge[e].c > edge[e].f)
			{
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}

	return level[T] != -1;
}

int Dfs(int u, int cap)
{
	if (u == T || cap <= 0)
		return cap;

	int flow = 0, subFlow;

	for (int e = head[u]; e != -1; e = edge[e].prev)
	{
		int v = edge[e].to;
		if (level[v] == level[u] + 1 && (subFlow = Dfs(v, std::min(cap, edge[e].c - edge[e].f))) > 0)
		{
			edge[e].f += subFlow;
			edge[e ^ 1].f -= subFlow;

			flow += subFlow;
			cap -= subFlow;

			if (cap == 0)
				break;
		}
	}

	if (flow == 0)
		level[u] = -1;

	return flow;
}

int Dinic()
{
	int maxFlow = 0;

	while (Bfs())
	{
		memcpy(curr, head, sizeof(head));
		maxFlow += Dfs(S, INF);
	}

	return maxFlow;
}

int distSq(int u, int v)
{
	return (xs[v] - xs[u]) * (xs[v] - xs[u]) + (ys[v] - ys[u]) * (ys[v] - ys[u]);
}

int main()
{
	int counter = 0;
	int t;

	while (_scanf("%d%d%d%d", &L, &W, &N, &d) != EOF && L != 0)
	{
		ec = 0;
		sqOf2d = (d * d) << 2;
		//upper corner = L, W => L is x-axis ???

		memset(head, -1, sizeof(head));
		//the size is not big, so no bother O(n) of memset

		S = N << 1;
		T = S + 1;

		t = N;

		for (int i = 0; i < N; ++i, ++t)
		{
			_scanf("%d%d", &xs[i], &ys[i]);

			addEdge(i, t, 1); //create a virtue edge !!

			if (ys[i] <= d)
			{
				addEdge(S, i, 1);
			}

			if ((ys[i] + d) >= W)
			{
				addEdge(t, T, 1);
			}

			for (int j = 0; j < i; ++j)
			{
				if (distSq(i, j) <= sqOf2d)
				{
					addEdge(t, j, 1);
					addEdge(j + N, i, 1);
				}
			}
		}

		printf("Case %d: %d\n", ++counter, Dinic());
	}

	return 0;
}
/*
500 300 5 100
250 0
250 150
250 300
100 150
400 150
*/