/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 79791
 * Submitted at:  2019-03-07 22:57:19
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    217
 * Problem Name:  Coin Change (UVa 674)
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <map>
#include <limits.h>

#define turn_on_fastIO                     \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);

#define _end '\n'
#define _tab '\t'
#define _scanf scanf

#define INF -INT_MAX
#define c_int const int

#define noOfCoins 5

const int MAX = 10000;
using namespace std;

int coins[noOfCoins]{1, 5, 10, 25, 50};
int memo[MAX];
int currentMAX;
int i, j, k;

int main()
{
    memo[0] = 1;
    int temp;

    while (_scanf("%d", &temp) != EOF)
    {
        if (memo[temp] == 0)
        {
            for (i = 0; i < noOfCoins; ++i)
            {
                k = temp - coins[i];
                for (j = currentMAX; j <= k; ++j)
                    memo[coins[i] + j] += memo[j];
            }
            currentMAX = temp;
        }
        printf("%d\n", memo[temp]);
    }

    return 0;
}