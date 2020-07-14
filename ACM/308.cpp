/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 81039
 * Submitted at:  2019-04-01 18:13:26
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    308
 * Problem Name:  Anti Brute Force Lock
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <bitset>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf

using namespace std;

#define keyLength 4
const int MAX_KEY = 501;
const int MAX_DISTANT = 40;

unsigned int keys[MAX_KEY][keyLength];
unsigned int dist[MAX_KEY][MAX_KEY];
bitset<MAX_KEY> visited;

struct edge
{
    int from, to, w;
    edge(int _f, int _t, int _w)
    {
        from = _f;
        to = _t;
        w = _w;
    }
};

auto cmp = [](edge a, edge b) { return a.w > b.w; };

int ans;
int noOfCase, noOfKey;

int d(int id_1, int id_2)
{
    int t, diff = 0;

    for (int i = 0; i < keyLength; ++i)
    {
        if (keys[id_1][i] > keys[id_2][i])
        {
            t = min(keys[id_1][i] - keys[id_2][i],
                    keys[id_2][i] - keys[id_1][i] + 10);
        }
        else
        {
            t = min(keys[id_2][i] - keys[id_1][i],
                    keys[id_1][i] - keys[id_2][i] + 10);
        }

        diff += t;
    }
    return diff;
}

int main()
{
    int i, j, t;

    _scanf("%d", &noOfCase);
    while (noOfCase--)
    {
        _scanf("%d", &noOfKey);

        if (noOfKey == 0)
            break;

        unsigned int next = 1;
        //keep keys[0] as inital state
        for (i = 1; i <= noOfKey; ++i)
        {
            _scanf(" %1d%1d%1d%1d", &keys[i][0], &keys[i][1], &keys[i][2], &keys[i][3]);
            dist[i][0] = dist[0][i] = d(i, 0);

            if (dist[0][next] > dist[0][i])
            {
                next = i;
            }
        }

        priority_queue<edge, vector<edge>, decltype(cmp)> moves(cmp);
        visited.reset();
        ans = dist[0][next];
        visited[next] = true;

        while (visited.count() != noOfKey)
        {
            for (i = 1; i <= noOfKey; ++i)
            {
                if (visited[i] == false)
                    moves.emplace(edge(next, i, d(next, i)));
            }

            do
            {
                next = moves.top().to;
                t = moves.top().w;
                moves.pop();
            } while (visited[next] == true && moves.empty() == false);

            ans += t;
            visited[next] = true;
        }

        printf("%d\n", ans);
    }

    return 0;
}