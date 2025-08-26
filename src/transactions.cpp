#include "transactions.h"
#include "util.h"


bool Transactions::deposit(Account *ac, double amt)
{
    if(amt > 0){
        ac->setBalance(ac->getBalance() + amt);   // updates acc balance
        str hist = str("Deposited ") + util::parseCurrency(amt) + str(" on ") + util::getTimeAndDate();
        ac->addHistory(hist);
        return true;
    }
    return false;
}
bool Transactions::withdraw(Account *ac, double amt)
{
    if (amt <= ac->getBalance())      //checks for valid amount to wthdraw
    {
        ac->setBalance(ac->getBalance() - amt);   // updates acc balance
        str hist = str("Withdrawed ") + util::parseCurrency(amt) + str(" on ") + util::getTimeAndDate();
        ac->addHistory(hist);
        return true;
    }
    return false;
}