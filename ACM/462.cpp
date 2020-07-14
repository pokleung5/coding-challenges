/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 81491
 * Submitted at:  2019-04-08 14:40:20
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    462
 * Problem Name:  Goldbach and Euler (UVa 10311)
 */

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

#define _end '\n'
#define _tab '\t'
#define _scanf scanf
#define _is_odd(num) (num & 1)

const int MAX = 100000000;
const int sqOfMAX = 10000;

int prime[sqOfMAX >> 1];
bool isp[sqOfMAX >> 1];
int primeCounter = 0;

bool isPrime(int n)
{
    if (n < sqOfMAX)
        return (n & 1) && isp[n >> 1];

    int sqOfN = sqrt(n);

    for (int i = 0; i < primeCounter && prime[i] <= sqOfN; ++i)
    {
        if (n % prime[i] == 0)
            return false;
    }

    return true;
}

int main()
{
    memset(isp, 1, sizeof(isp));
    prime[primeCounter++] = 2;
    isp[0] = false;

    for (int i = 3; i < sqOfMAX; i += 2)
    {
        if (isp[i >> 1] == true)
        {
            prime[primeCounter++] = i;
            int j = i << 1;

            while (j < sqOfMAX)
            {
                if (_is_odd(j))
                    isp[j >> 1] = false;
                j += i;
            }
        }
    }

    int a, t, i;
    while (_scanf("%d", &a) != EOF)
    {
        if (a & 1)
        {
            t = a - 2;
            if (isPrime(t))
                printf("%d is the sum of %d and %d.\n", a, 2, t);
            else
                printf("%d is not the sum of two primes!\n", a);
        }
        else
        {
            for (i = (a >> 1) - 1 - ((a >> 1) & 1); i > 0; i -= 2)
            {
                if (isPrime(i))
                {
                    t = a - i;
                    if (isPrime(t))
                    {
                        printf("%d is the sum of %d and %d.\n", a, i, t);
                        break;
                    }
                }
            }

            if (i <= 0)
            {
                t = a - 2;
                if (t != 2 && isPrime(t))
                    printf("%d is the sum of %d and %d.\n", a, 2, t);
                else
                    printf("%d is not the sum of two primes!\n", a);
            }
        }
    }

    return 0;
}