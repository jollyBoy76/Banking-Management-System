#include "menu.h"
#include "account.h"
#include <iostream>

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
        cout << "\n\n__BANKING SYSTEM__" << endl;
        cout << "1. Deposite" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Get current acc balance" << endl;
        cout << "4. Get acc details" << endl;
        cout << "5. Exit" << endl;

        // Taking choice input
        cout << "\nYour Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: {
            double amt;
            cout << "\nHow much do you want to deposit?" << endl;
            cin >> amt;
            if(ac.deposit(amt)){
                std::cout << "Deposit Succesful.\n" << amt << " Rs has been added to your account." << endl;
            } else { 
                std::cout << "Deposit Failed! Enter a Valid Amount." << endl;
            }
            break;
        }
            
        case 2:{
            double amt;
            cout << "\nHow much do you want to Withdraw?" << endl;
            cin >> amt;
            if (ac.withdraw(amt))
            {
                std::cout << "Withdrawal Successful.\n" << amt << " Rs has been deducted from your account." << endl;
            } else
            {
                std::cout << "Withdrawal Failed! Enter a Valid Amount." << endl;
            }
            break;
        }
            
        case 3:
            cout << "\n-----------------------------------" << endl;
            cout << "Current A/C Balance: " << ac.getBalance() << endl;
            cout << "-----------------------------------" << endl;
            break;
        case 4:
            cout << "\nPrinting account details...\n" << endl;
            ac.displayDetails();
            break;
        case 5:
            cout << "\nExiting..." << endl;
            break;
        
        default:
            cout << "\nInvalid Choice! " << endl;
            break;
        }

    } while (choice != 5);
}