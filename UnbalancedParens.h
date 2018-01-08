/* Phil Tenteromano
 * 12/7/2017
 * Data Structures
 * Final Project
 */

//Exception class for Unbalanced Parenthesis

#ifndef UNBALANCEDPARENS_H
#define UNBALANCEDPARENS_H

#include <string>

using namespace std;

class UnbalancedParens {
    public:
        UnbalancedParens()
        {
            message = "\nParenthesis are unbalanced or out of order.\n Try Again.\n";
        }

        string what()
        {
            return message;             //error message
        }
    private:
        string message;
};


#endif
