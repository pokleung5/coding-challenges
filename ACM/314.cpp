/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 80005
 * Submitted at:  2019-03-11 00:05:51
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    314
 * Problem Name:  Extend to Palindromes (UVa 11475)
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf

#define turn_on_fastIO                     \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);

using namespace std;

const int MAX = 100000 + 1;

char input[MAX];
char output[MAX];
int prevItr[MAX];

int len;
int lastItr;

void failure()
{
    static unsigned int i, j;
    i = 1;
    j = 0;

    prevItr[0] = 0;
    while (i < len)
    {
        if (output[i] == output[j])
        {
            ++j;
            prevItr[i] = j;
            ++i;
        }
        else if (j == 0)
        {
            prevItr[i] = 0;
            ++i;
        }
        else
        {
            j = prevItr[--j];
        }
    }
}

int KMP()
{
    static unsigned i, j, mark;
    i = 0;
    j = 0;
    while (i < len)
    {
        if (input[i] == output[j])
        {
            ++i;
            ++j;
        }
        else if (j == 0)
        {
            ++i;
        }
        else
        {
            j = prevItr[--j];
        }
    }
    return j;
}

int main()
{
    turn_on_fastIO;
    while (_scanf("%s", input) != EOF)
    {
        len = strlen(input);
        reverse_copy(input, input + len, output);
        output[len] = '\0';

        lastItr = len - 1;
        failure();

        cout << input << flush;
        cout << string(output).substr(KMP()) << _end;
    }

    return 0;
}