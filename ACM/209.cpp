/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 84074
 * Submitted at:  2019-04-28 22:55:05
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    209
 * Problem Name:  Isolated Segments (UVa 11343)
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>
#include <queue>

#define _scanf scanf
typedef std::pair<int, int> Point;
typedef std::pair<Point, Point> Line;

Line lines[105];
int noOfCase, noOfInput;

int orientation(Point p, Point q, Point r)
{
    long long int val = (q.first - p.first) * (r.second - p.second) -
                        (q.second - p.second) * (r.first - p.first);

    if (val < 0)
        return -1;

    return (val > 0);
}

bool onLine(Point u, Point v, Point p)
{
    return std::min(u.first, v.first) <= p.first &&
           std::max(u.first, v.first) >= p.first &&
           std::min(u.second, v.second) <= p.second &&
           std::max(u.second, v.second) >= p.second;
}

bool isIntersect(Line p, Line q)
{
    int d1, d2, d3, d4;
    d1 = orientation(p.first, p.second, q.first);
    d2 = orientation(p.first, p.second, q.second);
    d3 = orientation(q.first, q.second, p.first);
    d4 = orientation(q.first, q.second, p.second);

    // printf("%d %d %d %d\n", d1, d2, d3, d4);

    return (d1 * d2 < 0 && d3 * d4 < 0) ||
           (d1 == 0 && onLine(p.first, p.second, q.first)) ||
           (d2 == 0 && onLine(p.first, p.second, q.second)) ||
           (d3 == 0 && onLine(q.first, q.second, p.first)) ||
           (d4 == 0 && onLine(q.first, q.second, p.second));
}

int main()
{
    int counter;
    bool isolated;
    int x1, y1, x2, y2;

    _scanf("%d", &noOfCase);

    while (noOfCase--)
    {
        _scanf("%d", &noOfInput);

        counter = 0;
        for (int i = 0; i < noOfInput; ++i)
        {
            _scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            lines[i] = std::make_pair(std::make_pair(x1, y1),
                                      std::make_pair(x2, y2));
        }

        for (int i = 0; i < noOfInput; ++i)
        {
            isolated = true;
            for (int j = 0; j < noOfInput && isolated; ++j)
            {
                if (i != j)
                {
                    // printf("%d %d\n", i, j);
                    isolated = isIntersect(lines[i], lines[j]) == false;
                }
            }
            counter += isolated;
        }

        printf("%d\n", counter);
    }

    return 0;
}

/*
6
3 
0 0 2 0 
1 -1 1 1 
2 2 3 3 
2 
0 0 1 1 
1 0 0 1 
2 
0 0 0 1 
0 2 0 3 
2 
0 0 1 0 
1 0 2 0 
2 
0 0 2 2 
1 0 1 1 
2 
1 3 1 5 
1 0 1 6 

*/