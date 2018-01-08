/* Phil Tenteromano
 * 12/7/2017
 * Data Structures
 * Final Project
 */

//Calculator Implementation file
//using 3 custom-exception classes

#include "Calculator.h"

#include <cctype>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <map>

using namespace std;

//constructor assign empty strings
Calculator::Calculator()
{
    inFix = "";
    postFix = "";
}

//begins calculator functions
void Calculator::Begin()
{
    cout<<"Input any integer expression.\n"     //ask for input
        <<"You can use addition, subtraction, multiplication, division, and apply proper use of parenthesis:\n";
    getline(cin, inFix);     //ask for proper infix notation input, include whitespace

    ConvertandCheck(inFix);     //call primary function to check, convert expression

    cout<<endl;

    return;
}

//checking inFix for errors, converting to postFix along the way
void Calculator::ConvertandCheck(string exp)
{
    //immediately check for invalid operator use in front and last characters
    try {           //example: -3*2+ ... invalid
        if ( isOperator( exp.back()) || isOperator( exp.front()) )
            throw InvalidOpUse();
    } catch (InvalidOpUse obj) {
        cout<<obj.what();
        exit(1);            //exit program on exception (status 1)
    }

    //next, create stacks to convert, stack to test input
    stack <char> charStack;     //create the stack to convert to postFix
    stack <char> parenStack;    //needed to evaluate erroneous input

    //iterate through the inFix string evaluating each item
    for(unsigned int i=0; i<exp.size(); i++) {
        if ( whiteSpace(exp.at(i)) )    //get rid of excess whitespace
            continue;       //skip whitespace!
        //step 1 - check for operand, push onto PostFix
        else if ( isdigit(exp.at(i)) ) {    //add integers onto postfix string
            postFix.push_back( exp.at(i) );
        }   //will add a ' ' whitespace to end of all integers (confirms multi-digits)
       //step 2 - check for opening paren, push it
        else if( isOpenParen(exp.at(i)) ) {
            charStack.push(exp.at(i));  //used to build postFix - both paren/operators
            parenStack.push(exp.at(i)); //parenStack used to check open/close
        }
        //step 3 - check for operator to push/pop from stack
        else if ( isOperator( exp.at(i)) ) {        //checking +,-,*,/
            bool cycle; //create loop variable
            postFix.push_back(' ');  //add a space buffer for computation later
            do {
                cycle = false;      //break out of loop by default
                if ( charStack.empty() )     //push if stack is empty
                    charStack.push( exp.at(i) );
                else if( isOpenParen( charStack.top()) )
                    charStack.push( exp.at(i) );    //push if open paren is top
                else if ( isHigherPriority( exp.at(i), charStack.top()) )
                    charStack.push( exp.at(i) );    //higher priority goes onto stack
                else {     //otherwise, clear the stack while holding current operator
                    postFix.push_back( charStack.top());    //attach stack-top
                    postFix.push_back(' ');         //add white-space buffer
                    charStack.pop();     //pop and clear old top
                    cycle = true;       //reloop to find out where current operator goes
                }
            } while(cycle);     //loop until operator is on stack
        }
        //step 4 - check for closing parens
        else if ( isCloseParen(exp.at(i)) ) {   //closing paren
            try {       //throw exception if invalid input format
                if( parenStack.empty() )
                    throw UnbalancedParens();       //unbalanced exception
            } catch (UnbalancedParens obj1) {
                cout<<obj1.what();
                exit(1);          //exit program on exception (status 1)
            }
            //if no error, pop operators until open parens is encountered
            while ( isOperator( charStack.top()) && !charStack.empty()) {
                postFix.push_back(' ');     //buffer
                postFix.push_back(charStack.top());
                charStack.pop();        //add operators, pop
            }
            charStack.pop();    //pop the open parens off both stacks
            parenStack.pop();
        }
    } //for loop close

    //after the for loop**
    //unstack the remaining operators and append onto postFix
    while ( !charStack.empty() ) {
        postFix.push_back(' ');     //buffer
        postFix.push_back(charStack.top());     //add operator
        charStack.pop();                        //pop
    }
    //check for any remaining parens on stack one last time:
    try {       //throw exception if invalid input format
        if( !parenStack.empty() )
            throw UnbalancedParens();
    } catch (UnbalancedParens obj2) {
            cout<<obj2.what();
            exit(1);            //exit program on exception (status 1)
    }
    return;         //end conversion/check
}

//returns if character is an open parenthesis
bool Calculator::isOpenParen(char open)
{
    return (open == '(');
}
//returns if character is a closing parenthesis
bool Calculator::isCloseParen(char close)
{
    return (close == ')');
}

//returns if character is an operator
bool Calculator::isOperator(char op)
{
    if( op == '+' || op == '-' || op == '*' || op == '/')
        return true;
    else
        return false;
}

//this function compares the current op with the top of the stack operator
bool Calculator::isHigherPriority(char op, char top)
{
    //if op is mult or div, it is always high/same priority
    if(op == '*' || op == '/')
        return true;    //if op and top are ==, then same logic applies
    else if (top == '+' || top == '-')
        return true;
    else                //else op is add/sub, and top of stack has higher priority
        return false;
}

//checks for whitespace
bool Calculator::whiteSpace(char a)
{
    return (a == ' ');      //return value
}

//this function conducts single binary calculations on postfix expression
float Calculator::singleCompute(float op1, float op2, char optr)
{   //using floats for division operations
    switch(optr)        //find which operand, compute accordingly
    {
        case '*':
            return op1*op2;
        case '+':
            return op1+op2;
        case '-':
            return op2-op1;   //for sub/div, op2 is actually front operand
        case '/':
            try {
                if(op1 == 0)            //test for division by 0 here
                    throw DivByZero();
            } catch(DivByZero obj0) {
                cout<<obj0.what();
                exit(1);     //cannot divide by 0.. throw exception!!
            }
            return op2/op1;
    }
}

//returns the converted postFix expression
string Calculator::ShowPostFix()
{           //showing both expressions for easy comparison
    cout<<endl<<"Original inFix: "<<inFix<<endl;
    cout<<"Showing PostFix expression:"<<endl;
    return postFix;
}

//this function uses the private postFix member to convert
float Calculator::ComputePostFix()
{
    //using floats to get proper fractions when dividing
    float op1;      //stores first operand off stack
    float op2;      //stores second operand off stack
    float result;   //stores the result to return OR push onto stack
    char currentOp;    //character for current operation from postFix string
    string getValue = "";       //empty parsed string from postFix

    stack <float> numbers;        //values stored on stack to compute

    //loop through entire postFix string
    for(unsigned int i=0; i< postFix.length(); i++) {
        if(isNum( postFix.at(i)) )   //if number, push onto getValue string
            getValue.push_back( postFix.at(i) );
        //whitespace signals END of integer. Make sure previous is int, not operator
        else if (whiteSpace( postFix.at(i)) && !isOperator(postFix.at(i-1)) ) {
            op1 = StringtoInt(getValue);    //convert parsed string to int, save in op1
            numbers.push(op1);      //push op1 onto stack - first of 2 ops
            getValue.clear();       //clear the parsed string to get new value
        }   //find an operator, pop previous two operands off of the stack
        else if( isOperator( postFix.at(i)) ) {
            op1 = numbers.top();
            numbers.pop();      //pop top operand, op1 has its value
            op2 = numbers.top();
            numbers.pop();      //pop next operand, op2 has value
            currentOp = postFix.at(i);  //save the operator char to pass to compute funct
            result = singleCompute(op1, op2, currentOp);    //call compute function
            numbers.push(result);   //result saves the computation, push this onto stack
        }
        //result will act as new operand, until loop is over
    }
    return numbers.top();   //stack will have 1 item left, final RESULT
}

//using hash table
int Calculator::StringtoInt(string exp)
{
    //create hash table using 10 string to int values
    map<char, int> m;
    m['0'] = 0; m['1'] = 1; m['2'] = 2; m['3'] = 3; m['4'] = 4;
    m['5'] = 5; m['6'] = 6; m['7'] = 7; m['8'] = 8; m['9'] = 9;

    int result = 0; //starting value

    //loop through the string expression (getValue)
    for(int i=0; i<exp.size(); i++) {
        result += m[exp.at(i)]; //immediately find the character, convert to int
        result *= 10;           //multi-digit's, increase by factor of 10
    }
    return result/10;       //will be one extra zero after loop, so divide by 10
}

//self made function (could have used isdigit(char))
bool Calculator::isNum(char a)
{
    //array of all 10 digits
    int arr[10] = {'0','1','2','3','4','5','6','7','8','9'};

    //loop through, once number is found, return with bool
    for(int i=0; i<10; i++) {
        if(a == arr[i])
            return true;
    }

    return false;   //if not 0-9, return false
}

//fin
