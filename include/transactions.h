#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include "account.h" 


namespace Transactions
{
    bool deposit(Account *ac, double amt);
    bool withdraw(Account *ac, double amt);
    bool transferTo(Account *ac1, Account *ac2, double amt);
};

#endif