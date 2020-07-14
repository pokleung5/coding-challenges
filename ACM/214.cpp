/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 80767
 * Submitted at:  2019-03-25 18:36:36
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    214
 * Problem Name:  Prime difference
 */

// #define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <iterator>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf

#define turn_on_fastIO                     \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);

using namespace std;
const int MAX = 1299709 + 1;
const int noOfPrime = 100000 + 1;
bool isPrime[MAX];
int ans[MAX];
int prime[noOfPrime];

int main()
{
	int j, primeCounter = 0;
	memset(isPrime, true, MAX);

	int temp;
	void* address;

	for (int i = 2; i < MAX; ++i)
	{
		if (isPrime[i] == true)
		{
			if (primeCounter > 1) {
				temp = i - prime[primeCounter - 1];
				fill_n(&ans[prime[primeCounter - 1] + 1], temp - 1, temp);
			}
			temp = i;
			prime[primeCounter++] = i;
			j = i << 1;

			while (j < MAX)
			{
				isPrime[j] = false;
				j += i;
			}
		}
	}

	int a;

	while (_scanf("%d", &a) != EOF && a != 0)
	{
		printf("%d\n", ans[a]);
	}

	return 0;
}