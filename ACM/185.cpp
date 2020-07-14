/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 84894
 * Submitted at:  2019-05-03 17:32:50
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    185
 * Problem Name:  Andy's First Dictionary (UVa 10815)
 */

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <set>
#include <vector>

#define _lowerCase(c) (c | 0b00100000)
#define turn_on_fastIO                     \
    std::ios_base::sync_with_stdio(false); \
    std::cin.tie(NULL);

using std::string;

std::set<string> dict;

int main()
{
    string line, buf;

    turn_on_fastIO;

    while (getline(std::cin, line))
    {
        for (int i = 0, j = line.size(); i < j; ++i)
        {
            if (isalpha(line[i]))
                line[i] = _lowerCase(line[i]);
            else
                line[i] = ' ';
        }

        std::stringstream ss(line);

        while (ss >> buf)
            dict.insert(buf);
    }

    for (string t : dict)
    {
        std::cout << t << '\n';
    }
}