/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 84432
 * Submitted at:  2019-04-30 23:47:24
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    377
 * Problem Name:  Firing (PKU 2987)
 */


#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>

using std::min;
using std::queue;

const int maxV = 5000 + 10;
const int maxE = (60000 + maxV) << 1;
const int INF = 0x3f3f3f3f;

int V, E;
int S, T, ec;
int head[maxV], level[maxV], curr[maxV];

struct EDGE
{
    int to;
    int cap, flow;
    int prev;
} edge[maxE];

void AddEdge(int u, int v, int cap)
{
    edge[ec].to = v;
    edge[ec].cap = cap;
    edge[ec].flow = 0;
    edge[ec].prev = head[u];
    head[u] = ec++;

    edge[ec].to = u;
    edge[ec].cap = 0;
    edge[ec].flow = 0;
    edge[ec].prev = head[v];
    head[v] = ec++;
}

bool Bfs()
{
    memset(level, -1, sizeof(level));

    queue<int> q;
    q.push(S);
    level[S] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int e = head[u]; e != -1; e = edge[e].prev)
        {
            int v = edge[e].to;
            if (level[v] == -1 && edge[e].cap > edge[e].flow)
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
        if (level[v] == level[u] + 1 && (subFlow = Dfs(v, min(cap, edge[e].cap - edge[e].flow))) > 0)
        {
            edge[e].flow += subFlow;
            edge[e ^ 1].flow -= subFlow;

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

long long Dinic()
{
    long long maxFlow = 0;

    while (Bfs())
    {
        memcpy(curr, head, sizeof(head));
        maxFlow += Dfs(S, INF);
    }

    return maxFlow;
}

int _countFired(int u)
{
    // std::cout << u << ' ';
    level[u] = 1;

    int counter = 1;

    for (int e = head[u]; e != -1; e = edge[e].prev)
    {
        int v = edge[e].to;
        if (level[v] == -1 && edge[e].cap > edge[e].flow)
        {
            counter += _countFired(v);
        }
    }

    return counter;
}

int countFired()
{
    memset(level, -1, sizeof(level));
    return _countFired(S) - 1;
}

int main()
{
    long long int cap, sum;
    int u, v;

    while (scanf("%d%d", &V, &E) != EOF)
    {
        memset(head, -1, sizeof(head));

        ec = 0;
        sum = 0;

        S = 0;
        T = V + 1;

        for (int i = 1; i < T; ++i)
        {
            scanf("%lld", &cap);
            if (cap > 0)
            {
                sum += cap;
                AddEdge(S, i, cap);
            }
            else
            {
                AddEdge(i, T, -cap);
            }
        }

        while (E--)
        {
            scanf("%d%d", &u, &v);
            AddEdge(u, v, INF);
        }

        printf("%d %lld\n", countFired(), sum - Dinic());
    }

    return 0;
}

/*
5 5
8
-9
-20
12
-10
1 2
2 5
1 4
3 4
4 5
*/