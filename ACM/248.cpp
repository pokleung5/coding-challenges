/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 84676
 * Submitted at:  2019-05-02 01:57:24
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    248
 * Problem Name:  Intersection (UVa 191)
 */

#include <climits>
#include <cstring>
#include <algorithm>
#include <iostream>

#define _scanf scanf

int xs, ys, xe, ye; //line
int xl, yt, xr, yb; //rect

typedef std::pair<int, int> Point;
Point ps[6]; //0, 1 for line, other for rect

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

bool isIntersect(Point ps, Point pe, Point qs, Point qe)
{
    int d1, d2, d3, d4;
    d1 = orientation(ps, pe, qs);
    d2 = orientation(ps, pe, qe);
    d3 = orientation(qs, qe, ps);
    d4 = orientation(qs, qe, pe);
    // printf("%d %d %d %d\n", d1, d2, d3, d4);

    return (d1 * d2 < 0 && d3 * d4 < 0) ||
           (d1 == 0 && onLine(ps, pe, qs)) ||
           (d2 == 0 && onLine(ps, pe, qe)) ||
           (d3 == 0 && onLine(qs, qe, ps)) ||
           (d4 == 0 && onLine(qs, qe, pe));
}

bool test()
{
    for (int i = 2; i < 6; ++i)
    {
        for (int j = i + 1; j < 6; ++j)
        {
            if (isIntersect(ps[0], ps[1], ps[i], ps[j]))
            {
                return true;
                i = j = 6;
            }
        }
    }
    return false;
}
int main()
{
    int cc; // case count

    _scanf("%d", &cc);

    while (cc--)
    {
        _scanf("%d %d %d %d %d %d %d %d", &xs, &ys, &xe, &ye, &xl, &yt, &xr, &yb);

        if ((xs >= xl && xs <= xr && ys >= yb && ys <= yt) ||
            (xe >= xl && xe <= xr && ye >= yb && ye <= yt))
        {
            printf("T\n");
        }
        else
        {
            ps[0] = {xs, ys};
            ps[1] = {xe, ye};

            ps[2] = {xl, yt};
            ps[3] = {xr, yb};
            ps[4] = {xl, yb};
            ps[5] = {xr, yt};

            if (test() == true)
                printf("T\n");
            else
                printf("F\n");
        }
    }
    return 0;
}