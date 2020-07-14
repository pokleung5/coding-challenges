/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 76617
 * Submitted at:  2019-01-25 20:35:47
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    278
 * Problem Name:  Above Average (UVa 10370)
 */

#include <stdio.h>

int getInt(char eof)
{
	int result = 0;

	for (char input = getchar(); input != eof && input != '\n'; input = getchar())
		result = (result << 1) + (result << 3) + input - '0';

	return result;
}

int main()
{
	int **sets;
	double *mids;

	int c = getInt('\n');
	sets = new int *[c];
	mids = new double[c];

	for (int i = 0; i < c; i++)
	{
		int n = getInt(' ');
		sets[i] = new int[n + 1];
		sets[i][0] = n;
		mids[i] = 0;

		for (int j = 1, max = n +1; j < max; j++)
		{
			sets[i][j] = getInt(' ');
			mids[i] += sets[i][j];
		}
		mids[i] = mids[i] / n;
	}

	for (int i = 0; i < c; i++)
	{
		int counter = 0;
		int length = sets[i][0];

		for (int j = 1, max = length + 1; j < max; j++)
		{
			if (sets[i][j] > mids[i])
				counter++;
		}

		counter = (counter << 2) + (counter << 5) + (counter << 6);
		printf("%.3f%c\n", (float)counter / length, '%');
	}


	getchar();
	return 0;
}