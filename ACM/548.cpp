/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 80941
 * Submitted at:  2019-03-31 00:58:01
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    548
 * Problem Name:  Magic binary dot card
 */

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf
#define _rightmost(num) (num & (-num))
#define uli unsigned long int
using namespace std;

const int MAX_bit = 65;
// bitset<MAX_bit> bits;

uli a, b;
uli powerOf2[MAX_bit];

uli binarySearchClosestPowerOf2(uli n)
{
    int l = 0, r = 64;

    while (l <= r)
    {
        int m = ((l + r) >> 1);
        // cout << m << _tab;

        // cout << powerOf2[m - 1] << _tab;
        // cout << powerOf2[m] << _end;

        if (n > powerOf2[m - 1] && n <= powerOf2[m])
            return powerOf2[m];

        if (powerOf2[m] < n)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}

int main()
{
    uli temp;

    powerOf2[0] = 1;
    for (int i = 1; i < MAX_bit; ++i)
    {
        powerOf2[i] = powerOf2[i - 1] << 1;
    }

    while (scanf("%ld %ld", &a, &b) != EOF)
    {
        //1125899906842630 1125899906842632
        //printf("%ld %ld %ld\n", a, b, temp);
        if (a == b)
            printf("%ld\n", a);
        else
        {
            temp = (a | b) - a;
            if (temp != 0)
                printf("%ld\n", (binarySearchClosestPowerOf2(temp) - 1) | b);
        }
    }

    return 0;
}