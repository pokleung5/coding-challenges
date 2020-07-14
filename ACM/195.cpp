/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 76826
 * Submitted at:  2019-01-28 01:43:01
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    195
 * Problem Name:  Cellular Structure (UVa 620)
 */

#include <iostream>
#include <string>
using namespace std;

bool MUTANT;
string input;

void printStage()
{
    if (MUTANT)
        printf("MUTANT\n");
    else
    {
        if (input.at(input.length() - 1) == 'A')
            printf("MUTAGENIC\n");
        else
            printf("FULLY-GROWN\n");
    }
}

void checkStage(int &head, int &end)
{
    if (head >= end)
    {
        if (input.at(head) != 'A')
            MUTANT = true;
        return;
    }
    else
    {
        if (input.at(end--) == 'B')
        {
            if (input.at(end--) != 'A')
                MUTANT = true;
        }
        else
        {
            if (input.at(head++) != 'B')
                MUTANT = true;
        }

        if (!MUTANT)
            checkStage(head, end);
    }
}

int main()
{
    int noOfInput;
    int head, end;
    scanf("%d\n", &noOfInput);

    for (int i = 0; i < noOfInput; i++)
    {
        getline(cin, input);

        if (input == "A")
            printf("SIMPLE\n");
        else
        {
            MUTANT = !(input.length() & 1);
            if (!MUTANT)
            {
                head = 0;
                end = input.length() - 1;
                checkStage(head, end);
            }
            printStage();
        }
    }

    return 0;
}