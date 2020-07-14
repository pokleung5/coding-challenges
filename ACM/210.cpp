/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 84670
 * Submitted at:  2019-05-02 01:19:26
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    210
 * Problem Name:  Convex Hull Finding (maybe wrong) (UVa 681)
 */

#include <iostream>
#include <algorithm>
#include <queue>
#define _scanf scanf

const int maxV = 515;

struct Point
{
    int x, y, dSq;
} p[maxV];

int pc;

enum
{
    COLINEAR,
    CLOCKWISE,
    COUNTER_CLOCKWISE
};

int orientation(Point p, Point q, Point r) //cross product ab*ac
{
    int val = (q.x - p.x) * (r.y - p.y) -
              (q.y - p.y) * (r.x - p.x);

    if (val > 0)
        return COUNTER_CLOCKWISE;

    return (val < 0);
}

int downMost_Left;
void readPoints()
{
    downMost_Left = 0;

    for (int i = 0; i < pc; ++i)
    {
        _scanf("%d%d", &p[i].x, &p[i].y);

        if (p[i].y < p[downMost_Left].y)
            downMost_Left = i;
        else if (p[i].y == p[downMost_Left].y && p[i].x < p[downMost_Left].x)
            downMost_Left = i;
    }

    std::swap(p[0], p[downMost_Left]);

    for (int i = 1; i < pc; ++i)
    {
        p[i].dSq = (p[0].x - p[i].x) * (p[0].x - p[i].x) +
                   (p[0].y - p[i].y) * (p[0].y - p[i].y);
        // considered dSq might access more than once, memo !!
    }

    std::sort(p + 1, p + pc, [&](Point a, Point b) {
        int o = orientation(p[0], a, b);
        if (o == COLINEAR)
            return a.dSq < b.dSq;
        else
            return o == COUNTER_CLOCKWISE;
    });
}

int runGraham()
{
    int m = 1; // 0 is for left_down !!
    for (int i = 2; i < pc; ++i)
    {
        while (m > 0 &&
               orientation(p[m - 1], p[m], p[i]) == CLOCKWISE)
            --m;

        ++m;
        p[m] = p[i];
    }

    int fc = 1;
    for (int i = 2; i <= m; ++i)
    {
        if (orientation(p[fc - 1], p[fc], p[i]) == COLINEAR)
            p[fc] = p[i];
        else
            p[++fc] = p[i];
    }

    return fc + 1;
}

int main()
{
    int caseCount, m, count;

    _scanf("%d", &caseCount);
    printf("%d\n", caseCount);

    while (caseCount--)
    {
        _scanf("%d", &pc);
        readPoints();

        if (caseCount)
            _scanf("%d", &m); //get the -1

        count = runGraham();

        printf("%d\n", count + 1);

        for (int i = 0; i < count; ++i)
        {
            printf("%d %d\n", p[i].x, p[i].y);
        }

        printf("%d %d\n", p[0].x, p[0].y);

        if (caseCount)
            printf("-1\n");
    }

    return 0;
}
