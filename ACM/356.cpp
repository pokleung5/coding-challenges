/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 81912
 * Submitted at:  2019-04-18 16:32:44
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    356
 * Problem Name:  Poor Trade Advisor (UVa 11749)
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <limits.h>

#define _scanf scanf

const int MAX_N = 501;
const int MAX_E = 1000001;

int V, E;

struct Edge
{
    unsigned int u, v;
    int w;
};

unsigned int parent[MAX_N];
unsigned int height[MAX_N];
unsigned int maxCityCount;

unsigned int root(unsigned int u)
{
    if (parent[u] == 0)
        return u;
    parent[u] = root(parent[u]);
    return parent[u];
}

bool set_union(unsigned int a, unsigned int b)
{
    unsigned int root_a = root(a);
    unsigned int root_b = root(b);

    if (root_a != root_b)
    {
        if (height[root_a] > height[root_b])
        {
            parent[root_b] = root_a;
            height[root_a] += height[root_b];
            maxCityCount = std::max(height[root_a], maxCityCount);
        }
        else
        {
            parent[root_a] = root_b;
            height[root_b] += height[root_a];
            maxCityCount = std::max(height[root_b], maxCityCount);
        }
        return true;
    }
    return false;
}

void reset()
{
    std::fill_n(height, V, 1);
    std::memset(parent, 0, V * sizeof(int));
    maxCityCount = 0;
}

int main()
{
    int maxPPA;
    Edge edge;

    while (_scanf("%d%d", &V, &E) != EOF && V != 0)
    {
        ++V;

        maxPPA = INT_MIN;

        for (int i = 0; i < E; ++i)
        {
            _scanf("%d%d%d", &edge.u, &edge.v, &edge.w);
            if (edge.w > maxPPA)
            {
                reset();
                maxPPA = edge.w;
            }

            if (edge.w == maxPPA)
            {
                set_union(edge.u, edge.v);
            }
        }

        printf("%d\n", maxCityCount);
    }

    return 0;
}
