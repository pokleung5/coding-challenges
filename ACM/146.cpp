/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 80979
 * Submitted at:  2019-03-31 23:39:47
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    146
 * Problem Name:  Traffic Flow (UVa 10842)
 */

#include <iostream>
#include <algorithm>
#include <cstring>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf

using namespace std;

struct Edge
{
    int v1, v2, weight;
};

const int MAX_V = 10001;
const int MAX_E = 101;

Edge allEs[MAX_E];
int p[MAX_V];

int &parent(int v)
{
    if (p[p[v]] != p[v])
    {
        p[v] = parent(p[v]);
    }
    return p[v];
}

int main()
{
    int V, E, v1, v2, root;
    int noOfInput;

    _scanf("%d", &noOfInput);

    for (int k = 1; k <= noOfInput; ++k)
    {
        _scanf("%d %d", &V, &E);
        
        if (V == 0 && E == 0)
            break;

        for (int i = 0; i < E; ++i)
        {
            _scanf("%d %d %d", &allEs[i].v1, &allEs[i].v2, &allEs[i].weight);
        }

        sort(allEs, allEs + E, [&](Edge a, Edge b) {
            return a.weight > b.weight;
        });

        // printf("%d %d\n", V, E);

        for (int i = 0; i < V; ++i)
        {
            p[i] = i;
        }

        for (int e = 0; e < E; ++e)
        {
            // cout << allEs[e].v1 << ' ' << allEs[e].v2 << ' '
            //      << allEs[e].weight << _end;

            v1 = allEs[e].v1;
            v2 = allEs[e].v2;

            if (parent(v1) == v1 && parent(v2) != v2)
            {
                parent(v1) = parent(v2);
            }
            else if (parent(v2) == v2 && parent(v1) != v1)
            {
                parent(v2) = parent(v1);
            }
            else if (parent(v1) != parent(v2))
            {
                parent(parent(v2)) = parent(v1);
            }

            root = parent(0);
            // cout << _tab << 0 << _tab << parent(0) << _end;
            // cout << _tab << 1 << _tab << parent(1) << _end;

            for (int i = 1; root == parent(i); ++i)
            {
                // cout << _tab << i << _tab << parent(i) << _end;
                if (i >= V - 1)
                {
                    printf("Case #%d: %d\n", k, allEs[e].weight);
                    e = E;
                    break;
                }
            }
        }
    }
    return 0;
}
