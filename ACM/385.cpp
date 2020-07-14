/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 84682
 * Submitted at:  2019-05-02 02:49:27
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    385
 * Problem Name:  Useless Tile Packers
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

#define _scanf scanf

const int maxV = 106;

struct Point
{
    int x, y; //, dSq;
} ps[maxV];

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
        _scanf("%d%d", &ps[i].x, &ps[i].y);

        if (ps[i].y < ps[downMost_Left].y)
            downMost_Left = i;
        else if (ps[i].y == ps[downMost_Left].y && ps[i].x < ps[downMost_Left].x)
            downMost_Left = i;
    }
}

int runGraham()
{
    std::swap(ps[0], ps[downMost_Left]);

    // no need check colinear given in statement
    // for (int i = 1; i < pc; ++i)
    // {
    //     ps[i].dSq = (ps[0].x - ps[i].x) * (ps[0].x - ps[i].x) +
    //                 (ps[0].y - ps[i].y) * (ps[0].y - ps[i].y);
    //     // considered dSq might access more than once, memo !!
    // }

    std::sort(ps + 1, ps + pc, [&](Point a, Point b) {
        int o = orientation(ps[0], a, b);
        // if (o == COLINEAR)
        //     return a.dSq < b.dSq;
        // else
        return o == COUNTER_CLOCKWISE;
    });

    int m = 1; // 0 is for left_down !!
    for (int i = 2; i < pc; ++i)
    {
        while (m > 0 &&
               orientation(ps[m - 1], ps[m], ps[i]) == CLOCKWISE)
            --m;

        ++m;
        ps[m] = ps[i];
    }

    return m + 1;

    // no need check colinear given in statement
    // int fc = 1;
    // for (int i = 2; i <= m; ++i)
    // {
    //     if (orientation(ps[fc - 1], ps[fc], ps[i]) == COLINEAR)
    //         ps[fc] = ps[i];
    //     else
    //         ps[++fc] = ps[i];
    // }

    // return fc + 1;
}

int cross(Point p, Point q, Point r) //cross product ab*ac
{
    return (q.x - p.x) * (r.y - p.y) -
           (q.y - p.y) * (r.x - p.x);
}

int main()
{
    int caseCount = 0, sum, newCount;
    int areaT2, newAreaT2;

    while (_scanf("%d", &pc) != EOF && pc != 0)
    {
        readPoints();

        areaT2 = 0;
        for (int i = 2; i < pc; ++i)
            areaT2 += cross(ps[0], ps[i - 1], ps[i]);

        newCount = runGraham();

        newAreaT2 = 0;
        for (int i = 2; i < newCount; ++i)
            newAreaT2 += cross(ps[0], ps[i - 1], ps[i]);

        printf("Tile #%d\n", ++caseCount);
        printf("Wasted Space = %.2lf %%\n\n", (double)(abs(newAreaT2) - abs(areaT2)) * (100) / abs(newAreaT2));
    }

    return 0;
}