#ifndef UTIL_H
#define UTIL_H

#include <string>

/*
These funcs can be used in other modules to organise code and avoid repetition.

*getValidatedInt and getValidatedDouble can take int or double input with error handling to code doesn't 
crash during executoin

*parseCurrency can format money into desired currency so that we don't repeat formating for each we print some ammount.

*clrscr stands for clearscreen, it executes cls on the shell terminal.

*/

namespace util
{
    int getValidatedInt(int min, int max); // min and max can be used to set limit to input amount (;/)
    double getValidatedDouble();
    std::string parseCurrency(double amt);
    void clrscr();
    void getscr();
}


#endif