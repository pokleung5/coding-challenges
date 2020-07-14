/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 84518
 * Submitted at:  2019-05-01 15:22:45
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    563
 * Problem Name:  Pahom on Water
 */

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>

#define _scanf scanf
#define INF INT_MAX
#define FLOAT_EQUAL(a, b) (fabs(a - b) < 1e-9)
// at least on path from 400 to 789 and from 789 to 400
// if a's color > b's color => red to violet
// if a's color < b's color => violet to red
// just extra condition for sendFlow ??
// start from 400 => means 2 or more path from S to T
// can walk only intersect

const int maxV = 305;
const int maxE = 200000;

struct Circle
{
	int x, y, r;
	double color;
} p[maxV];

struct EDGE
{
	int to, prev;
	int c, f;
} edge[maxE];

int S, T, ec; // S connect all 400, T connect all 789;
int head[maxV], level[maxV], curr[maxV];

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

bool isIntersect(Circle a, Circle b)
{
	return (a.r + b.r) * (a.r + b.r) >=
		((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main()
{
	int noOfCase, noOfPads;
	_scanf("%d", &noOfCase);

	while (noOfCase--)
	{
		_scanf("%d", &noOfPads);

		ec = 0;
		S = 0;
		T = noOfPads - 1;

		memset(head, -1, sizeof(head));

		for (int i = 0; i < noOfPads; ++i)
		{
			_scanf("%lf %d %d %d", &p[i].color, &p[i].x, &p[i].y, &p[i].r);
		}

		std::sort(p, p + noOfPads, [&](Circle a, Circle b) {
			return a.color < b.color;
		});

		for (int i = 0; i < noOfPads; ++i)
		{
			for (int j = i + 1; j < noOfPads; ++j)
			{
				if (isIntersect(p[i], p[j]))
				{
					addEdge(i, j, 1);
				}
			}
		}

		if (Dinic() > 1)
			printf("Game is VALID\n");
		else
			printf("Game is NOT VALID\n");
	}

	return 0;
}