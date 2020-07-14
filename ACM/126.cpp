/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 77507
 * Submitted at:  2019-02-11 14:11:58
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    126
 * Problem Name:  Risk (UVa 567)
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#define NUM 21
using namespace std;

int visited[NUM] = {0};
int dist[NUM][NUM] = {0};
string temp;
stringstream ss;
int noOfInput, nodeID, nodeID2, counter = 0;
int step;

int MIN(int a, int b)
{
    return a > b ? b : a;
}

class Node
{
  public:
    int nodeID;
    //vector<Node *> previous;
    vector<Node *> adjNodes;

    Node(int nodeID)
    {
        this->nodeID = nodeID;
    }

    int distTo(int nodeID)
    {
        ++step;

        int minDist = NUM;

        for (int i = adjNodes.size(); i-- > 0;)
        {
            if (adjNodes.at(i)->nodeID == nodeID)
                return 1;

            if (visited[adjNodes.at(i)->nodeID] == 0 || visited[adjNodes.at(i)->nodeID] > step)
            {
                visited[adjNodes.at(i)->nodeID] = step;
                minDist = MIN(minDist, adjNodes.at(i)->distTo(nodeID));
                visited[adjNodes.at(i)->nodeID] = 0;
            }
        }

        return minDist + 1;
    }
};

Node *map[NUM];

int main()
{

    while (getline(cin, temp) && temp != "")
    {
        for (int i = 1; i < NUM; i++)
        {
            map[i] = new Node(i);
        }

        for (int i = 1; i < 20; i++)
        {

            ss.clear();
            ss << temp;
            ss >> noOfInput;

            while (noOfInput-- > 0)
            {
                ss >> nodeID;
                map[i]->adjNodes.push_back(map[nodeID]);
                map[nodeID]->adjNodes.push_back(map[i]);
            }

            getline(cin, temp);
        }

        ss.clear();
        ss << temp;
        ss >> noOfInput;

        printf("Test Set #%d\n", ++counter);

        while (noOfInput-- > 0)
        {
            getline(cin, temp);
            ss.clear();
            ss << temp;
            ss >> nodeID;
            ss >> nodeID2;

            step = 0;

            if (nodeID2 > nodeID)
                printf("%2d to %2d: %d\n", nodeID, nodeID2, map[nodeID]->distTo(nodeID2));
            else
                printf("%2d to %2d: %d\n", nodeID, nodeID2, map[nodeID2]->distTo(nodeID));
        }

        printf("\n");

        for (int i = 1; i < NUM; i++)
        {
            delete map[i];
        }
    }

    return 0;
}
