/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 81143
 * Submitted at:  2019-04-02 14:49:58
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    361
 * Problem Name:  The Super Power (UVa 11752)
 */

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <cstring>
#include <cmath>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf_s
#define ull unsigned long long int

const ull MAX_NO = ~0;
const double log_MAX_NO = 64 * log10(2);
const int max_power = 65;

bool isPrime[max_power];

const ull max_basic_num = 1 << 16;

int main()
{

    std::set<ull> ans;

    ull cur;
    ull i, j;
    int max;

    memset(isPrime, 1, sizeof(isPrime));
    for (i = 2; i < max_power; ++i)
    {
        if (isPrime[i] == true)
        {
            j = i << 1;
            while (j < max_power)
            {
                isPrime[j] = false;
                j += i;
            }
        }
    }

    for (i = 2; i < max_basic_num; ++i)
    {
        // so that i^max < MAX_NO
        max = ceil(log_MAX_NO / log10(i)) - 1;
        // first non prime is 4, so i^4
        cur = i * i * i * i;
        ans.insert(cur);

        for (j = 5; j <= max; ++j)
        {
            cur *= i;
            if (isPrime[j] == false)
            {
                ans.insert(cur);
            }
        }
        // if ((j - 1) != ((ceil(64 * log(2) / log(i)) - 1)))
        // std::cout << i << _tab << j - 1 << _tab << ceil(64 * log(2) / log(i)) - 1 << _end;
    }

    printf("1\n");
    for (ull a : ans)
    {
        printf("%llu\n", a);
    }

    return 0;
}