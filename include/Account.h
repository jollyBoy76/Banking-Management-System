#ifndef ACCOUNT_H
#define ACCOUNT_H


// #include <iostream>
#include <string>

typedef std::string str;


class Account

{
private:
    str name;
    int accountNumber;
    double balance;
        
public:
    Account( str accName, int accNum, double accBalance);

    bool deposit(double amount);
    bool     withdraw(double amount);
    double getBalance() const;      // "const" is decelered to make sure this function desn't modify any class variable
    void displayDetails() const;    
    
};


#endif