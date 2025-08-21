#include "transactions.h"

bool Transactions::deposit(Account &ac, double amt)
{
    if(amt > 0){
        ac.setBalance(ac.getBalance() + amt);   // updates acc balance
        return true;
    }
    return false;
}
bool Transactions::withdraw(Account &ac, double amt)
{
    if (amt <= ac.getBalance())      //checks for valid amount to wthdraw
    {
        ac.setBalance(ac.getBalance() - amt);   // updates acc balance
        return true;
    }
    return false;
}