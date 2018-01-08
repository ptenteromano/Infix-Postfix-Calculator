/* Phil Tenteromano
 * 12/7/2017
 * Data Structures
 * Final Project
 */

//main driver program

#include <iostream>
#include "Calculator.h"

using namespace std;

int main()
{   //no need to try/catch in main... Calculator calls exit(1) on exceptions
    Calculator calc;

    calc.Begin();           //begin calculation

    cout<<calc.ShowPostFix()<<endl;       //show new post-fix expression

    cout<<endl<<"\nYour result is....!?\n"
        <<calc.ComputePostFix();


    return 0;
}
