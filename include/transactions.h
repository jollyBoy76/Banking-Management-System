#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include "account.h" 


namespace Transactions
{
    bool deposit(Account &ac, double amt);
    bool withdraw(Account &ac, double amt);
};

#endif