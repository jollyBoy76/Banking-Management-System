#include "Account.h"
#include <iostream>

//class Construtor

using std::cout;

Account::Account(str accName, int accNum, double accBalance)
{
    name = accName;
    accountNumber = accNum;
    balance = accBalance;
}


bool Account::deposit(double amount) {
    if (amount <=0)
    {
        return false;
    }
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (amount > balance) {
        cout << "Insufficient funds!" << std::endl;
        return false;
    } 
    else {
        balance -= amount;
        return true;
    }
}

double Account::getBalance() const {
    return balance;
}

void Account::displayDetails() const {
    cout << "Account Number: " << accountNumber << "\n";
    cout << "Name: " << name << "\n";
    cout << "Balance: " << balance << "\n";
}