/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 84812
 * Submitted at:  2019-05-03 03:47:01
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    174
 * Problem Name:  Minimum Transport Cost (UVa 523)
 */

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <climits>
#include <string>

#define maxSize 1000
#define maxCost 10000000
//no given max N and max cost ....

int dist[maxSize][maxSize];
int next[maxSize][maxSize];
int tax[maxSize];
int V;

void runFloydWarshall()
{
    int i, j, k, temp;

    for (k = 1; k <= V; ++k)
        for (i = 1; i <= V; ++i)
            for (j = 1; j <= V; ++j)
            {
                temp = dist[i][k] + dist[k][j] + tax[k];
                if (temp < dist[i][j])
                {
                    dist[i][j] = temp;
                    next[i][j] = next[i][k];
                }
            }
}

int main()
{
    int cc, w, t, from, to;
    int ttc; //total cost
    char temp_c;
    char buf[maxSize];
    bool started;

    scanf("%d", &cc);
    while (cc--)
    {
        V = 0;
        do
        {
            ++V; //why the hell will it start at 1 ...
            scanf("%d%c", &w, &temp_c);
            //std::cout << w << ' ';
            dist[1][V] = (w == -1) ? maxCost : w;
            next[1][V] = V;
        } while (temp_c == ' ');

        for (int i = 2; i <= V; ++i)
        {
            for (int j = 1; j <= V; ++j)
            {
                scanf("%d", &w);
                //std::cout << w << ' ';
                dist[i][j] = (w == -1) ? maxCost : w;
                next[i][j] = j;
            }
            //std::cout << '\n';
        }

        for (int i = 1; i <= V; ++i)
        {
            scanf("%d\n", &t); //avoid \n affect fgets
            tax[i] = t;
        }

        runFloydWarshall();
        // no terminator also ... just a line break ????????
        // buf should at least have 2 digit 1 space 1 '\n'

        while (fgets(buf, maxSize, stdin) && strlen(buf) > 3)
        {
            // thank you for uDebug !!
            if (started)
                printf("\n");
            else
                started = true;

            sscanf(buf, "%d %d", &from, &to);

            printf("From %d to %d :\n", from, to);

            ttc = dist[from][to];
            printf("Path: %d", from);

            while (from != to)
            {
                from = next[from][to];
                printf("-->%d", from);
            }

            printf("\nTotal cost : %d\n", ttc);
        }
    }
    return 0;
}

//         for (int i = 1; i <= V; ++i)
//         {
//             for (int j = 1; j <= V; ++j)
//             {
//                 std::cout << dist[i][j] << ' ';
//             }
//             std::cout << '\n';
//         }
