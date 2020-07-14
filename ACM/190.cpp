/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 76874
 * Submitted at:  2019-01-28 21:10:05
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    190
 * Problem Name:  Equation (UVa 727)
 */

#include <iostream>
#include <stdio.h>
#include <string>
#define isOperator(opr) (opr == '+' || opr == '-' || opr == '*' || opr == '/')
#define isEOF(opr) (opr == ')' || opr == '\n')
#define priority(op) ((op == '*' || op == '/') ? 1 : 0)
#define MAX_INPUT 50

using namespace std;

char *output;
int itr = 0;

class Stack
{
    struct Stack_element
    {
        Stack_element *previous;
        char element;
    };

    Stack_element *top_element = NULL;

  public:
    bool isEmpty()
    {
        return this->top_element == NULL;
    }

    void push(char c)
    {
        this->top_element = new Stack_element({top_element, c});
    }

    char top()
    {
        return this->top_element->element;
    }

    char pop()
    {
        Stack_element *temp = this->top_element;

        char data = temp->element;
        top_element = temp->previous;

        delete temp;
        return data;
    }

    void popUntil(char c)
    {
        char temp = this->pop();
        while (temp != c)
        {
            output[itr++] = temp;
            temp = this->pop();
        }
    }

    void popUntilEmpty()
    {
        while (!this->isEmpty())
        {
            output[itr++] = this->pop();
        }
    }
};

Stack *stack = new Stack();

void handleC(char c)
{
    bool pushC;

    if (isOperator(c))
    {
        do
        {
            pushC = stack->isEmpty() || stack->top() == '(' || priority(c) > priority(stack->top());

            if (pushC)
                stack->push(c);
            else
            {
                output[itr++] = stack->pop();
            }
        } while (!pushC);
    }
    else if (c == '(')
    {
        stack->push(c);
    }
    else if (c == ')')
    {
        stack->popUntil('(');
    }
    else
        output[itr++] = c;
}

char getCharInLine()
{
    char c;
    do
    {
        c = getchar();
        if (c == 10)
        {
            c = getchar();
            if (c == 10 || c == EOF)
                return '\n';
        }
    } while (c == 13 || c == 10);

    return c;
}

int main()
{
    int noOfInput;
    string temp;

    cin >> noOfInput;
    getchar();
    getline(cin, temp);

    char c;
    output = new char[MAX_INPUT];

    for (int num = 0; num < noOfInput; num++)
    {
        //printf("\n%d\n", num);
        while (getline(cin, temp) && temp != "")
        {
            c = temp.at(0);
            if (c == 13)
                break;

            //printf("(%d)", c);
            handleC(c);
        }

        stack->popUntilEmpty();

        output[itr] = '\0';

        if (num != 0)
            printf("\n");
        printf("%s\n", output);
        itr = 0;
    }

    delete output;
    delete stack;
    return 0;
}