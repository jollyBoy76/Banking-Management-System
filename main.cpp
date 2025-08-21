//#include "menu.h"
#include "util.h"
#include "account.h"
#include <iostream>

int main()
{

    // Menu menu; // Menu class deceleration

    // std::cout << "Starting BMS...\n"
    //           << std::endl;
    // menu.run(); // Executing menu which contains all the other features
    // std::cout << "\n...BMS Stopped" << std::endl;

    Account::loadFromFile("data/accounts.txt");
    
    Account::createAcc("Sachin", "sachin.sy1441@gmail.com", "1234567890", "RPS more, Danapur, Patna", "16-04-2005");
    Account::createAcc("Sahil", "sahil.sh231@gmail.com", "1235453209", "RPS more, Danapur, Patna", "21-07-2005");

    Account* user1 = Account::signInAcc(1);

    std::cout << user1->getUserName() << std::endl;
    std::cout << user1->getEmail() << std::endl;
    std::cout << user1->getPhoneNum() << std::endl;
    std::cout << user1->getAddress() << std::endl;
    std::cout << user1->getDOB() << std::endl;
    std::cout << user1->getBalance() << "\n\n"<< std::endl;

    Account* user2 = Account::signInAcc(2);

    std::cout << user2->getUserName() << std::endl;
    std::cout << user2->getEmail() << std::endl;
    std::cout << user2->getPhoneNum() << std::endl;
    std::cout << user2->getAddress() << std::endl;
    std::cout << user2->getDOB() << std::endl;
    std::cout << user2->getBalance() << std::endl;

    Account::saveToFile("data/accounts.txt");
    
    std::cout << "Press ANY KEY to close the Window.";
    util::getscr();

    return 0;
}