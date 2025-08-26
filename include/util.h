#ifndef UTIL_H
#define UTIL_H

#include <string>

typedef std::string str;

/*
These funcs can be used in other modules to organise code and avoid repetition.

*getValidatedInt and getValidatedDouble can take int or double input with error handling to code doesn't 
crash during executoin

*getValidatedEmail takes a user input string and maches it with emailformat from regex to return a valid email string.

*take ValidatedPassword takes:

Minimum length (e.g., 8 characters).

At least one uppercase letter.

At least one lowercase letter.

At least one digit.

At least one special character (like !@#$%^&*).

*parseCurrency can format money into desired currency so that we don't repeat formating for each we print some ammount.

*clrscr stands for clearscreen, it executes cls on the shell terminal.

*/

namespace util
{
    int getValidatedInt(int min, int max); // min and max can be used to set limit to input amount (;/)
    double getValidatedDouble();
    std::string getValidatedEmail();
    bool isValidPassword(const std::string& password);
    std::string getValidatedPassword();
    std::string getValidatedName();
    std::string getValidatedPhoneNum();
    std::string getValidatedAddress();
    std::string getValidatedDOB();
    std::string getValidatedAccType();
    std::string parseCurrency(double amt);
    std::string getTimeAndDate();
    void clearInputBuffer();
    void clrscr();
    void getscr();
}


#endif