/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 83858
 * Submitted at:  2019-04-27 19:51:03
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    373
 * Problem Name:  Falling Pineapple From Sky
 */

#include <stdio.h>
#include <algorithm>
#include <cstring>

#define maxV 1005
#define maxE 25005
#define _scanf scanf

struct Kruskal
{
    struct Edge
    {
        int u, v, w;
    };

    Edge edges[maxE];
    int parent[maxV];
    bool used[maxE];

    int find(int e)
    {
        if (parent[e] < 0)
            return e;
        return parent[e] = find(parent[e]);
    }

    void _unionSet(int r1, int r2)
    {
        parent[r1] += parent[r2];
        parent[r2] = r1;
    }

    void unionSet(int r1, int r2)
    {
        if (parent[r1] < parent[r2])
            _unionSet(r1, r2);
        else
            _unionSet(r2, r1);
    }

    int run(int V, int E)
    {
        std::sort(edges, edges + E, [&](Edge e1, Edge e2) {
            return e1.w < e2.w;
        });

        memset(parent, -1, V * sizeof(int));
        memset(used, false, E);

        int minCost = 0;
        int noEdgeNeed = V;
        int r1, r2;

        for (int i = 0; i < E; ++i)
        {
            r1 = find(edges[i].u);
            r2 = find(edges[i].v);

            if (r1 != r2)
            {
                unionSet(r1, r2);
                minCost += edges[i].w;
                used[i] = true;
                --noEdgeNeed;
            }

            if (noEdgeNeed == 1)
                return minCost;
        }

        return -1;
    }
};

// To make it faster, just record the used edges, instead of unused edges !!!
int main()
{
    // freopen("in", "r", stdin);

    int V, E;
    int w, u, v;
    int minCost;
    int i;

    Kruskal kk;

    while (_scanf("%d%d", &V, &E) != EOF && V > 0)
    {
        for (i = 0; i < E; ++i)
            _scanf("%d%d%d", &kk.edges[i].u, &kk.edges[i].v, &kk.edges[i].w);

        minCost = kk.run(V, E);

        if (minCost > 0)
        {
            printf("Min cost: %d\n", minCost);

            i = 0;
            while (kk.used[i] == true && i < E)
                ++i;

            if (i < E)
            {
                printf("%d", kk.edges[i++].w);

                for (; i < E; ++i)
                {
                    if (kk.used[i] == false)
                    {
                        printf(" %d", kk.edges[i].w);
                    }
                }
            }
            printf("\n");
        }
        else
        {
            printf("\\(^o^)/ pray to god\n");
        }
    }
};