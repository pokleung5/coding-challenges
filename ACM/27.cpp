/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 77184
 * Submitted at:  2019-02-01 20:37:25
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    27
 * Problem Name:  Gems in the maze
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#define MAX(a, b) (a > b ? a : b)

int a, b, c, v, N;
bool *entered;
int max;

int nextRoom()
{
	int temp = (v * (a * v + b) + c) % N;

	if (v == temp)
		return -1;
	else
		return temp;
}

int countGems(int rm)
{

	if (entered[rm] || rm == -1)
		return 0;

	entered[rm] = true;
	return countGems(v = nextRoom()) + 1;
	// if (count[rm] == -1)
	// {
	// 	count[rm] = countGems(v = nextRoom()) + 1;
	// }

	// return count[rm];
}

int main()
{
	int noOfInput;
	int temp;

	scanf("%d", &noOfInput);
	// printf("%d\n", noOfInput);

	for (int t = 0; t < noOfInput; t++)
	{

		//std::getline(std::cin, temp);

		scanf("%d %d %d %d", &a, &b, &c, &N);

		//printf("%d %d %d %d\n", a, b, c, N);

		entered = new bool[N];

		max = 0;

		for (int i = 0; i < N; i++)
		{
			memset(entered, 0, N);
			temp = countGems(v = i);
			max = MAX(max, temp);
		}

		printf("%d\n", max);
		delete entered;
	}
	return 0;
}