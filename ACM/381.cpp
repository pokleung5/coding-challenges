/*****************************************
 * (This comment block is added by the Judge System)
 * Submission ID: 77236
 * Submitted at:  2019-02-02 20:31:41
 *
 * User ID:       621
 * Username:      54795701
 * Problem ID:    381
 * Problem Name:  Hexadecimal Calculation
 */

#include <stdio.h>
#include <iostream>
#include <string>
#define MAX_INPUT 100
#define isDigit(c) ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'))
#define isOperator(opr) (opr == '+' || opr == '*')
#define isEOF(opr) (opr == ')' || opr == '\n')
#define priority(op) ((op == '*') ? 1 : 0)

using namespace std;
template <class T>
class Stack
{
    struct Stack_element
    {
        Stack_element *previous;
        T element;
    };

    Stack_element *top_element = NULL;

  public:
    bool isEmpty()
    {
        return this->top_element == NULL;
    }

    void push(T c)
    {
        this->top_element = new Stack_element({top_element, c});
    }

    T top()
    {
        return this->top_element->element;
    }

    T pop()
    {
        Stack_element *temp = this->top_element;

        T data = temp->element;
        top_element = temp->previous;

        delete temp;
        return data;
    }
};

Stack<char> *stack = new Stack<char>();
Stack<int> *operands = new Stack<int>();

char convertToHex(int value)
{
    switch (value)
    {
    case 10:
        return 'A';
    case 11:
        return 'B';
    case 12:
        return 'C';
    case 13:
        return 'D';
    case 14:
        return 'E';
    case 15:
        return 'F';
    }

    return value + '0';
}

int convertToDec(char value)
{
    switch (value)
    {
    case 'A':
        return 10;
    case 'B':
        return 11;
    case 'C':
        return 12;
    case 'D':
        return 13;
    case 'E':
        return 14;
    case 'F':
        return 15;
    }

    return value - '0';
}

void printInHex(int value)
{
    if (value > 0)
    {
        printInHex(value >> 4);
        printf("%c", convertToHex(value & 15));
    }
}

int resultOf(int operand_1, int operand_2, char opr)
{
    int result;

    switch (opr)
    {
    case '*':
        result = operand_1 * operand_2;
        break;
    case '+':
        result = operand_1 + operand_2;
        break;
    }

    return result;
}

void handleExpression(char c)
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
                operands->push(resultOf(operands->pop(), operands->pop(), stack->pop()));

        } while (!pushC);
    }
    else if (c == '(')
    {
        stack->push(c);
    }
    else if (c == ')')
    {
        for (char temp = stack->pop(); temp != '('; temp = stack->pop())
            operands->push(resultOf(operands->pop(), operands->pop(), temp));
    }
    else if (isDigit(c))
        operands->push(convertToDec(c));
}

int main()
{
    char c;
    int result;
    string input;

    while (getline(cin, input) && input != "")
    {

        for (int i = 0, j = input.length(); i < j; i++)
        {
            c = input.at(i);
            handleExpression(c);
        }

        while (!stack->isEmpty())
        {
            operands->push(resultOf(operands->pop(), operands->pop(), stack->pop()));
        }

        result = operands->pop();
        if (result == 0)
            printf("0\n");
        else
        {
            printInHex(result);
            printf("\n");
        }
    }

    delete operands;
    delete stack;
    return 0;
}

//getline(cin,string2)
