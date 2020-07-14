/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 78205
 * Submitted at:  2019-02-24 15:33:15
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    165
 * Problem Name:  Frogger (UVa 534) (Precision)
 */

#include <iostream>
#include <algorithm>
#include <math.h>

#define turn_on_fastIO                     \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);

#define _scanf scanf

using namespace std;

int square[1001];
int _squareOf(int x)
{
    x = abs(x);
    if (square[x] == 0)
        square[x] = x * x;
    return square[x];
}

int noOfInput;
struct point
{
    int x;
    int y;
};

const int MAX = 200;
point pt[MAX];
int dist[MAX][MAX];

int distSquare(point &a, point &b)
{
    return _squareOf(a.x - b.x) + _squareOf(a.y - b.y);
}

int main()
{
    int counter = 0;
    while (true)
    {

        _scanf("%d", &noOfInput);

        if (noOfInput == 0)
            return 0;

        for (int i = 0; i < noOfInput; i++)
        {
            _scanf("%d %d", &pt[i].x, &pt[i].y);
        }

        for (int i = 0; i < noOfInput; i++)
        {
            for (int j = -(~i); j < noOfInput; j++)
            {
                dist[i][j] = dist[j][i] = distSquare(pt[i], pt[j]);
                //cout << dist[i][j] << '\t' << i << '\t' << j << '\n';
            }
        }

        for (int i = 0; i < noOfInput; i++)
        {
            for (int j = 0; j < noOfInput; j++)
            {
                for (int k = -(~j); k < noOfInput; k++)
                {
                    dist[k][j] = dist[j][k] = min(dist[j][k], max(dist[j][i], dist[i][k]));
                    //cout << dist[i][j] << '\t' << i << '\t' << j << '\t' << k << '\n';
                }
            }
        }

        printf("Scenario #%d\nFrog Distance = %.3f\n\n", ++counter, sqrt(dist[0][1]));
    }

    return 0;
}