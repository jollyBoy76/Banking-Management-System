#include "menu.h"
#include "account.h"
#include "util.h"
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;

void Menu::run()
{

    Account ac("Sachin", 1234, 750.25); // creating an account
    int choice;

    do
    {
        // Displaying Menu
        util::clrscr();     //clearing terminal
        cout << "\n\n__BANKING SYSTEM__" << endl;
        cout << "1. Deposite" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Get current acc balance" << endl;
        cout << "4. Get acc details" << endl;
        cout << "5. Exit" << endl;

        // Taking choice input
        cout << "\nYour Choice: ";
        choice = util::getValidatedInt(1,5);

        switch (choice)
        {
        case 1: {
            util::clrscr();     //clearing terminal
            double amt;
            cout << "\nHow much do you want to deposit?" << endl;
            amt = util::getValidatedDouble();
            if (cin.fail()) {
                cin.clear(); // clear error flags
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input! Please enter a number.\n";
                util::getscr(); //wait for user to press enter
                break;
            }
            if(ac.deposit(amt)){
                std::cout << "Deposit Succesful.\n" << util::parseCurrency(amt) << " has been added to your account." << endl;
            } else { 
                std::cout << "Deposit Failed! Enter a Valid Amount." << endl;
            }
            util::getscr();
            break;
        }
            
        case 2:{
            util::clrscr();     //clearing terminal
            double amt;
            cout << "\nHow much do you want to Withdraw?" << endl;
            amt = util::getValidatedDouble();
            if (cin.fail()) {
                cin.clear(); // clear error flags
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input! Please enter a number.\n";
                util::getscr();
                break;
            }
            if (ac.withdraw(amt))
            {
                std::cout << "Withdrawal Successful.\n" << util::parseCurrency(amt) << " Rs has been deducted from your account." << endl;
            } else
            {
                std::cout << "Withdrawal Failed! Enter a Valid Amount." << endl;
            }
            util::getscr();
            break;
        }
            
        case 3:
            util::clrscr();     //clearing terminal
            cout << "\n-----------------------------------" << endl;
            cout << "Current A/C Balance: " << util::parseCurrency(ac.getBalance()) << endl;
            cout << "-----------------------------------" << endl;
            util::getscr();
            break;
        case 4:
            util::clrscr();     //clearing terminal
            cout << "\nPrinting account details...\n" << endl;
            ac.displayDetails();
            util::getscr();
            break;
        case 5:
            util::clrscr();     //clearing terminal
            cout << "\nExiting..." << endl;
            break;
        
        }

    } while (choice != 5);
}