/* Phil Tenteromano
 * 12/7/2017
 * Data Structures
 * Final Project
 */

//Exception class for Division by ZERO



#ifndef DIVBYZERO_H
#define DIVBYZERO_H

#include <string>

using namespace std;

class DivByZero {
    public:
        DivByZero()
        {
            message = "\nIllegal Division by Zero\n Try Again.\n";
        }
        string what()
        {
            return message;     //error message
        }
    private:
        string message;
};

 #endif // DIVBYZERO_H
