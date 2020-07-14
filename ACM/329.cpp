/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 80367
 * Submitted at:  2019-03-15 17:21:10
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    329
 * Problem Name:  Super string? Shortest?
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf

#define turn_on_fastIO                     \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);

using namespace std;

const int MAX = 1001;

char input1[MAX];
char input2[MAX];

int len1, len2;
int memo[MAX][MAX];

int LCS(int l1, int l2)
{
	if (l1 < 0 || l2 < 0)
		return 0;

	if (memo[l1][l2] < 0)
	{
		if (input1[l1] == input2[l2])
			memo[l1][l2] = 1 + LCS(l1 - 1, l2 - 1);
		else
			memo[l1][l2] = max(LCS(l1 - 1, l2), LCS(l1, l2 - 1));
	}

	return memo[l1][l2];
}

int main()
{
	turn_on_fastIO;

	int noOfInput;

	_scanf("%d", &noOfInput);
	while (noOfInput--)
	{
		_scanf("%s", input1);
		_scanf("%s", input2);
		len1 = strlen(input1);
		len2 = strlen(input2);
		memset(memo, -1, sizeof(memo));

		cout << len1 + len2 - LCS(len1 - 1, len2 - 1) << _end;
	}

	return 0;
}