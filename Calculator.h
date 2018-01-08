/* Phil Tenteromano
 * 12/7/2017
 * Data Structures
 * Final Project
 */

//Calculator Specification file

#ifndef CONVERT_H
#define CONVERT_H

#include "DivByZero.h"
#include "InvalidOpUse.h"
#include "UnbalancedParens.h"

#include <string>


using namespace std;

class Calculator
{
    public:
        Calculator();       //constructor
        void Begin();       //Begins the call to objects functions
        string ShowPostFix();   //returns the newly converted string

        float ComputePostFix(); //Computes the new PostFix expression

    private:
        string inFix;       //initial infix expression
        string postFix;     //converted expression

        //primary two functions used to convert and compute
        void ConvertandCheck(string exp);
        float singleCompute(float op1, float op2, char optr);

        //self-made functions to check, convert
        int StringtoInt(string exp);        //using hash-table
        bool isOpenParen(char open);
        bool isCloseParen(char close);
        bool isOperator(char op);
        bool isHigherPriority(char op, char top);
        bool whiteSpace(char a);
        bool isNum(char a);

};


#endif // CALCULATOR_H



