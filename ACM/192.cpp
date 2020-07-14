/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 76797
 * Submitted at:  2019-01-27 16:19:49
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    192
 * Problem Name:  Not so Mobile (UVa 839)
 */

#include <stdio.h>

bool isMobile = true;
int subWeight()
{
    int w1, d1, wr, dr;
    scanf("%d %d %d %d", &w1, &d1, &wr, &dr);

    if (w1 == 0)
    {
        w1 = subWeight();
    }

    if (wr == 0)
    {
        wr = subWeight();
    }

    if (w1 == -1 || wr == -1)
        return -1;

    if (w1 * d1 == wr * dr)
        return w1 + wr;
    else
        return -1;
}

int main()
{
    int noOfCase;
    scanf("%d", &noOfCase);
    getchar();

    for (int i = 0; i < noOfCase; i++)
    {
        getchar();
        if (i != 0)
            printf("\n");

        if (subWeight() > 0)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}