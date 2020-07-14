/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 77861
 * Submitted at:  2019-02-18 19:13:21
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    438
 * Problem Name:  Party
 */

#include <stdio.h>
#define _max(a, b) (a ^ ((a ^ b) & -(a < b)))

int main()
{

    int noOfInput;
    scanf("%d", &noOfInput);

    int N;
    while (noOfInput--)
    {
        // as to keep most people, they must all know 1 person A who will leave just before them, assuming they all have N - 1 friends, person A would have x - 1 friends. And the person who lost person A would have x - 1 friends also, and gonna left before others.
        scanf("%d", &N);
        printf("%d\n", _max(N - 2, 0));
    }

    return 0;
}
