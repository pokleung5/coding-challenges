/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 80917
 * Submitted at:  2019-03-30 01:47:08
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    143
 * Problem Name:  Slim Span - Tokyo Regional 07 (LA 3887)
 */

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <vector>
#include <cstring>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf

using namespace std;

const int MAX_noOfEdge = (9900 >> 1) + 1;
const int MAX_noOfVertix = 100 + 1;

//https://blog.csdn.net/xiao_k666/article/details/79254366
struct Edge
{
	int v1, v2, weight;
};

Edge allEs[MAX_noOfEdge];
int p[MAX_noOfVertix];

int &parent(int v)
{
	if (p[v] == 0)
	{
		p[v] = v;
	}
	else if (p[p[v]] != p[v])
	{
		p[v] = parent(p[v]);
	}
	return p[v];
}

int main()
{
	int V, E;
	int v1, v2, weight;

	while (_scanf("%d %d", &V, &E) != EOF)
	{
		if (V == 0 && E == 0)
			break;

		for (int i = 0; i < E; ++i)
		{
			_scanf("%d %d %d", &allEs[i].v1, &allEs[i].v2, &allEs[i].weight);
		}
		// printf("\n%d %d %d\n", allEs[0].v1, allEs[0].v2, allEs[0].weight);

		sort(allEs, allEs + E, [&](Edge a, Edge b) {
			return a.weight < b.weight;
		});

		unsigned int ans = -1;
		//TODO : make sure all nodes are connected
		int s, e, v1, v2, root;

		for (s = 0; s < E; ++s)
		{
			memset(p, 0, (V + 1) * sizeof(int));
			for (e = s; e < E; ++e)
			{
				// for (int i = 1; i <= V; ++i)
				// {
				// 	printf("%d\t", p[i]);
				// }
				// printf("\n%d %d %d\n", allEs[e].v1, allEs[e].v2, allEs[e].weight);

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

				root = parent(V);
				for (int i = V - 1; root == parent(i); --i)
				{
					if (i == 1)
					{
						ans = min(ans, (unsigned int)allEs[e].weight - allEs[s].weight);
						// printf("\t\t\t%d\n", (signed int)allEs[e].weight - allEs[s].weight);
						e = E;
						break;
					}
				}
			}
			if (ans == -1)
				break;
		}

		printf("%d\n", (signed int)ans);
	}

	return 0;
}