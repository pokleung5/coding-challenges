/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 79916
 * Submitted at:  2019-03-09 22:22:10
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    218
 * Problem Name:  SuperSale (UVa 10130)
 */

#include <iostream>
#include <algorithm>
#include <cstring>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf

#define c_int const int

using namespace std;

c_int result_max = 30 + 1;
c_int objs_max = 1000 + 1;
c_int result_size = result_max * sizeof(int);

int result[result_max];
int objs_w[objs_max];
int objs_p[objs_max];

int main()
{
    int noOfInput;
    int noOfObject;
    int noOfPeople;
    int temp1, temp2;

    _scanf("%d", &noOfInput);
    while (noOfInput--)
    {
        _scanf("%d", &noOfObject);
        for (int i = 0; i < noOfObject; ++i)
        {
            _scanf("%d %d", &objs_p[i], &objs_w[i]);
        }

        memset(result, 0, result_size);
        for (int i = 0; i < noOfObject; ++i)
        {
            for (int j = result_max - objs_w[i] - 1; j >= 0; --j)
            {
                //cout << j << _tab << objs_w[i] << endl;
                temp1 = j + objs_w[i];
                result[temp1] = max(result[temp1], result[j] + objs_p[i]);
            }
        }

        _scanf("%d", &noOfPeople);
        temp2 = 0;
        while (noOfPeople--)
        {
            _scanf("%d", &temp1);
            temp2 += result[temp1];
        }
        printf("%d\n", temp2);
    }

    return 0;
}