/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 85286
 * Submitted at:  2019-05-05 14:12:21
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    207
 * Problem Name:  Minimum Effort
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

#define maxSize 205
using namespace std;

int V, E;

vector<int> graph[maxSize];
int dist[maxSize][maxSize];
int parent[maxSize];
bool visited[maxSize];
int pathDist[maxSize];
std::stack<int> path;

const int maxNameLen = 16;
map<string, int> places;
map<int, string> itp; //index to place

void init()
{
	places.clear();
	itp.clear();

	for (int i = 0; i < V; ++i)
	{
		graph[i].clear();
		memset(dist[i], -1, V * sizeof(int));
	}
}

void addEdge(int u, int v, int w, int rw)
{
	graph[u].emplace_back(v);
	graph[v].emplace_back(u);
	dist[u][v] = std::min<unsigned int>(dist[u][v], w);
	dist[v][u] = std::min<unsigned int>(dist[v][u], rw); // so -1 will be very big
}

typedef pair<int, int> State;
void runDijkstra(int src, int target)
{
	memset(parent, -1, V * sizeof(int));
	memset(visited, false, V);
	fill_n(pathDist, V, -INT_MAX);

	priority_queue<State> q;
	q.emplace(0, src);
	parent[src] = src;
	pathDist[src] = 0;

	int newD;
	while (q.size())
	{
		int d = q.top().first, u =  q.top().second;
		q.pop();

		visited[u] = true;
		
		for (int v : graph[u])
		{
			newD = d - dist[u][v];
			// parent[v] == -1 && 
			if (visited[v] == false && dist[u][v] > 0 && newD > pathDist[v])
			{
				q.emplace(newD, v);
				parent[v] = u; 
				pathDist[v] = newD;
			}
		}
	}

	if (parent[target] != -1) 
	{
		for (int i = target; i != src; i = parent[i])
			path.emplace(i);
	}
}

char fastscan(int &x)
{
	register int c;
	x = 0;
	c = getchar();

	for (; (c > 47 && c < 58); c = getchar())
		x = (x << 1) + (x << 3) + c - 48;

	return c; //return the terminator
}

void printPath(int src, int end)
{
	if (src != end)
	{
		printPath(src, parent[end]);
		cout << " -> " << itp[end];
	}
}

int main()
{
	string buf, buf2;
	char buf_c[maxNameLen];
	int u, v, w1, w2, total_w;

	while (scanf("%d\n", &V) != EOF)
	{
		// printf("%d\n", V);
		V += 2;

		init();

		for (int i = 2; i < V; ++i)
		{
			getline(cin, buf, '\n');
			// buf = buf.substr((i != 2), buf.size());
			places.emplace(buf, i);
			itp.emplace(i, buf);
			//first '\n' is catch so first no need substr
		}

		places["office"] = 0;
		itp[0] = "office";
		places["hall"] = 1;
		itp[1] = "hall";

		scanf("%d\n", &E);
		for (int i = 0; i < E; ++i)
		{
			getline(cin, buf, ':');
			u = places[buf];

			getline(cin, buf, ' ');
			while (places.find(buf) == places.end())
			{
				getline(cin, buf2, ' ');
				buf.append(" " + buf2);
			}
			v = places[buf];

			if (fastscan(w1) == ' ')
				fastscan(w2);
			else
				w2 = -1;

			// cout << (int)getchar() << '\t';

			addEdge(u, v, w1, w2);
		}

		runDijkstra(1, 0);
		total_w = -1 * pathDist[0];
		runDijkstra(0, 1);
		total_w += -1 * pathDist[1];

		cout << total_w <<'\n' ;
		cout << itp[0];

		while (path.size())
		{
			u = path.top();
			path.pop();
			cout << " -> " << itp[u];
		}

		printf("\n\n");
	}
	return 0;
}