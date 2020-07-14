/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 80581
 * Submitted at:  2019-03-21 18:03:57
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    156
 * Problem Name:  Everlasting...?
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf

using namespace std;

const int MAX = 1000001;

int prime_factor_sol(int x)
{
    int i = 3;
    int accum = 0;

    int c = x;

    while ((c & 1) == 0)
        c >>= 1;

    if (c != x)
    {
        if (c == 1)
            return 2;

        accum += 2;
        // cout << 2 << _tab;
    }

    while (i * i <= c)
    {
        x = c;

        while ((c % i) == 0)
            c /= i;

        if (c != x)
        {
            if (c == 1)
                return i - accum;

            accum += i;
            // cout << i << _tab;
        }

        i += 2;
    }

    // cout << c << _end;
    return c - accum;
}

int main()
{
    int a, b;

    while (_scanf("%d %d", &a, &b))
    {
        if (a == 0 && b == 0)
            break;

        if (prime_factor_sol(a) > prime_factor_sol(b))
            printf("a\n");
        else
            printf("b\n");
    }
    return 0;
}