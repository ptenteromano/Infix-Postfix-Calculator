/* Phil Tenteromano
 * 12/7/2017
 * Data Structures
 * Final Project
 */

 //Exception class for invalid operator input

#ifndef INVALIDOPUSE_H
#define INVALIDOPUSE_H

#include <string>

using namespace std;

class InvalidOpUse {
    public:
        InvalidOpUse()
        {
            message = "\nInvalid input, operators need 2 operands.\n Try Again.\n";
        }
        string what()
        {
            return message;     //error message
        }
    private:
        string message;
};

#endif
