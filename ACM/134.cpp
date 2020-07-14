/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 77568
 * Submitted at:  2019-02-11 22:46:39
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    134
 * Problem Name:  Dominos 2 (UVa 11518)
 */

#include <stdio.h>
#include <cstring>
#include <vector>
#include <set>

using namespace std;
class node;

int noOfInput;
int n, m, l;
bool *falls;
int noOfFell;
int temp1, temp2;

node** elements;

class node {
public :
	int _nodeID;
	set<int> adjNodes;

	node(int _nodeID){
		this->_nodeID = _nodeID;
	}

	int size() {

		if (falls[_nodeID] == true)
			return 0;

		int counter = 0;
		falls[_nodeID] = true;

		for(auto _temp : adjNodes){

			if (falls[_temp] == false) {
				counter += elements[_temp]->size();
			}
		}

		return counter + 1;
	}

};


int main()
{

	scanf("%d", &noOfInput);
	while (noOfInput-- > 0)
	{
		scanf("%d %d %d", &n, &m, &l);
		falls = new bool[n + 1];
		memset(falls, 0, n + 1);

		elements = new node*[n + 1];

		for (int i = 1; i <= n; i++) {
			elements[i] = new node(i);
		}

		while (m-- > 0)
		{
			scanf("%d %d", &temp1, &temp2);
			elements[temp1]->adjNodes.insert(temp2);
		}

		noOfFell = 0;
		while (l-- > 0)
		{
			scanf("%d", &temp1);
			noOfFell += elements[temp1]->size();
		}

		printf("%d\n", noOfFell);

		for (int i = 1; i <= n; i++) {
			delete elements[i];
		}
		delete falls;
	}

	return 0;
}