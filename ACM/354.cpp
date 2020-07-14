/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 76581
 * Submitted at:  2019-01-25 19:15:01
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    354
 * Problem Name:  Credit Check (UVa 11743)
 */

#include <stdio.h>

int getInt(char eof)
{
    int result = 0;

    for (char input = getchar(); input != eof && input != '\n'; input = getchar())
        result = (result << 1) + (result << 3) + input - '0';

    return result;
}

bool isEndWithZero(int value)
{
    switch (value)
    {
    case 30:
    case 40:
    case 50:
    case 60:
    case 70:
    case 80:
    case 90:
    case 100:
    case 110:
    case 120:
    case 130:
    case 140:
        return true;
        break;
    }
    return false;
}

int getUnitsDigitAfterDouble(int value)
{
    switch (value)
    {
    case 0:
    case 5:
        return 0;
        break;
    case 1:
    case 6:
        return 2;
        break;
    case 2:
    case 7:
        return 4;
        break;
    case 3:
    case 8:
        return 6;
        break;
    case 4:
    case 9:
        return 8;
        break;
    }
    return value;
}

int main()
{
    int noOfInput = getInt('\n');
    int *numbersTotal = new int[noOfInput];
    bool doubleTheValue = true;

    for (int i = 0; i < noOfInput; i++)
    {
        for (int input = getchar(); input != '\n'; input = getchar())
        {
            if (input != ' ')
            {
                input = input - '0';
                if (doubleTheValue)
                {
                    numbersTotal[i] += getUnitsDigitAfterDouble(input);
                    if (input > 4)
                    {
                        numbersTotal[i] += 1;
                    }
                }
                else
                {
                    numbersTotal[i] += input;
                }
                doubleTheValue = !doubleTheValue;
            }
        }
    }

    for (int i = 0; i < noOfInput; i++)
    {
        if (isEndWithZero(numbersTotal[i]))
        {
            printf("Valid\n");
        }
        else
        {
            printf("Invalid\n");
        }
    }
}