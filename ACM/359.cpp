/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 76880
 * Submitted at:  2019-01-28 22:42:25
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    359
 * Problem Name:  Simple Computers (CO assignment?)
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

typedef unsigned char Byte;

bool terminated = false;
Byte *memory = (Byte *)malloc(32);
Byte *accu = (Byte *)malloc(1);
Byte *pc = (Byte *)malloc(1);

void printByte(int value, int noOfBit)
{
    if (noOfBit > 1)
        printByte(value >> 1, noOfBit - 1);
    printf("%d", value & 1);
}

void operate(int code)
{
    *pc = *pc + 1;
    if (*pc > 31)
        *pc -= 31;

    int operand = code & 31;

    switch (code >> 5)
    {
    case 0:
        *(memory + operand) = *accu;
        break;
    case 1:
        *accu = *(memory + operand);
        break;
    case 2:
        if (*accu == 0)
            *pc = operand;
        break;
    case 3:
        break;
    case 4:
        *accu = *accu - 1;
        break;
    case 5:
        *accu = *accu + 1;
        break;
    case 6:
        *pc = operand;
        break;
    case 7:
        terminated = true;
        printByte(*accu, 8);
        printf("\n");
        break;
    }
}

int main()
{
    string temp;
    char c;
    unsigned int value;

    do
    {
        *accu = 0;
        *pc = 0;
        terminated = false;

        for (int i = 0; i < 32; i++)
        {
            value = 0;
            getline(cin, temp);

            if (temp == "")
                return 0;

            for (int j = 0; j < 8; j++)
            {
                c = temp.at(j);
                value = ((value << 1) | (c - '0'));
            }

            *(memory + i) = value;
        }

        while (!terminated)
        {
            operate(*(memory + *pc));
        }

    } while (true);

    delete pc;
    delete accu;
    delete memory;
    return 0;
}