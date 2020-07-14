/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 85145
 * Submitted at:  2019-05-04 01:10:30
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    259
 * Problem Name:  Brackets sequence (easy ver.)
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <climits>
#include <string>
#include <cstring>

const int maxN = 105;
const int INF = 1000;
int dp[maxN][maxN];
bool start = true;

int main()
{
    int noOfCase;
    scanf("%d\n", &noOfCase);
    // std::string input;
    char input[maxN], temp[maxN];
    int len, counter;

    while (noOfCase--)
    {
        if (start)
            start = false;
        else
            printf("\n");

        fgets(input + 1, maxN, stdin);
        // printf("%s\n", input + 1);
        fgets(temp, maxN, stdin);
        // printf("%s\n", temp);

        // scanf("%s\n", input + 1);
        len = strlen(input + 1) - 1;
        // printf("%d\t", len);

        if (len < 2)
        {
            printf("%d\n", len * 2);
            continue;
        }

        memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= len; i++)
        {
            dp[i][i] = 1;
        }

        for (int j = 1; j <= len; ++j)
        {
            for (int i = j - 1; i >= 1; --i)
            {
                dp[i][j] = dp[i + 1][j] + 1;

                for (int k = i + 1; k <= j; ++k)
                {
                    if ((input[i] == '(' && input[k] == ')') || (input[i] == '[' && input[k] == ']'))
                    {
                        dp[i][j] = std::min(dp[i][j], dp[i + 1][k - 1] + dp[k + 1][j]);
                    }
                }
            }
        }

        printf("%d\n", len + dp[1][len]);
    }

    return 0;
}

//                    if ((input[i] == '(' && input[k] == ')') || (input[i] == '[' && input[k] == ']'))
