/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 79498
 * Submitted at:  2019-03-02 22:57:35
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    172
 * Problem Name:  Rough Roads (UVa 10356)
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <limits.h>

#define turn_on_fastIO                     \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);

#define _end '\n'
#define _tab '\t'
#define _is_odd(num) (num & 1)

#define _scanf scanf

using namespace std;

inline void _assign_min(int &loc, unsigned int c)
{
    if (loc <= 0 || loc > c)
        loc = c;
}

class Graph
{
  public:
    //! maybe need > >
    unordered_map<int, unordered_map<int, int>> adjList;

    void clear()
    {
        adjList.clear();
    }

    void addEdge(int &a, int &b, int &c)
    {
        _assign_min(adjList[a][b], c);
        _assign_min(adjList[b][a], c);
    }

    int dijkstra(int v, int t)
    {
        unordered_map<int, int> discovered;
        multimap<int, int> q;
        int temp_w;

        q.emplace(0, v);

        while (!q.empty())
        {
            auto top = q.begin();
            v = top->second;

            if (v == t)
                return top->first;

            if (discovered[v] < 2)
            {
                ++discovered[v];
                // cout << v << _tab << top->first << _end;

                for (auto u : adjList[v])
                {
                    temp_w = top->first + u.second;

                    for (auto u2 : adjList[u.first])
                    {
                        if (discovered[u2.first] < 2)
                        {
                            // cout << _tab << temp_w + u2.second << _tab << u2.first << _end;
                            q.emplace(temp_w + u2.second, u2.first);
                        }
                    }
                }
            }
            q.erase(top);
        }

        return -1;
    }
};

int temp;
Graph g;

int main()
{
    int n, r;
    int a, b, w;
    int counter = 0;

    while (_scanf("%d %d", &n, &r) != EOF)
    {
        g.clear();

        while (r--)
        {
            _scanf("%d %d %d", &a, &b, &w);
            g.addEdge(a, b, w);
        }

        w = g.dijkstra(0, n - 1);

        printf("Set #%d\n", ++counter);
        if (w == -1)
            printf("?\n");
        else
            printf("%d\n", w);
    }
    return 0;
}