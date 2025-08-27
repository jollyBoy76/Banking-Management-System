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

bool Transactions::transferTo(Account *ac1, Account *ac2, double amt){
    if(amt > ac1->getBalance()){
        return false;
    }
    else{
        ac1->setBalance(ac1->getBalance() - amt);   // deducting amount from sender account
        ac2->setBalance(ac2->getBalance() + amt);   // deposting amount to reciever account
        str hist1 = str("Transferred ") + util::parseCurrency(amt) + str(" to A/C No: ") + std::to_string(ac2->ID) + str(", on ") + util::getTimeAndDate();
        str hist2 = str("Recieved ") + util::parseCurrency(amt) + str(" from A/C No: ") + std::to_string(ac1->ID) + str(", on ") + util::getTimeAndDate();
        ac1->addHistory(hist1);
        ac2->addHistory(hist2);
        return true;
    }
}