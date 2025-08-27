// Includes
#include "util.h"
#include "account.h"
#include "transactions.h"
#include "user.h"
#include "help.h"
#include <iostream>

// Aliases
using namespace std;
using namespace util;
typedef std::string str;

// Functions

int load()
{
    bool flag1, flag2, flag3, flag4;
    flag1 = User::loadUsersFromFile("data/users.txt");
    
    flag2 = User::loadPasswordsFromFile("data/passwords.txt");
    flag3 = Account::loadAccountsFromFile("data/accounts.txt");
    // loads each accounts history
    for (auto& pair : Account::accounts) {
    flag4 = pair.second.loadHistoryFromFile(str("data/Account_histories/history_") + std::to_string(pair.first) + str(".txt"));
    }
    if(flag1 == false || flag2 == false || flag3 == false || flag4 == false){
        cerr << "File Not Open!" << endl;
        return -1;
    }

}

int save()
{
    bool flag1, flag2, flag3, flag4;
    flag1 = User::saveUsersToFile("data/users.txt");
    flag2 = User::savePasswordsToFile("data/passwords.txt");
    flag3 = Account::saveAccountsToFile("data/accounts.txt");
    // Saves history of each account
    for (const auto& pair : Account::accounts) {
        flag4 = pair.second.saveHistoryToFile(str("data/Account_histories/history_") + std::to_string(pair.first) + str(".txt"));
    }
    if(flag1 == false || flag2 == false || flag3 == false || flag4 == false){
        cerr << "File Not Open!" << endl;
        getscr();
        return -1;
    }
}

int main_menu()
{
clrscr();
    cout << "===============================" << endl;
    cout << "|| BANKING MANAGEMENT SYSTEM ||" << endl;
    cout << "===============================" << endl;
    cout << "\n1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;

    cout << "\nYour Choice: ";
    int pick = util::getValidatedInt(1, 3);
    return pick;
}

User *registeration()
{
    UserData user_data;

    while (true)
    {
        user_data.name = getValidatedName();
        // Checking if username is available
        if (!(User::loadByUsername(user_data.name) == nullptr))
        {
            cout << "User Name Not Available! Try Agian." << endl;
        }
        else
        {
            cout << "Name Accepted!";
            break;
        }
    }
    user_data.email = getValidatedEmail();
    user_data.phone = getValidatedPhoneNum();
    user_data.add = getValidatedAddress();
    user_data.dob = getValidatedDOB();

    // creatinn user
    User *usr = User::createUser(user_data);
    usr->createPassword();

    return usr;
}

User *login()
{
    str name, pass;

    User *user;

    // Usrename check
    while (true)
    {
        name = util::getValidatedName();
        user = User::loadByUsername(name);
        if (user == nullptr)
        {
            cerr << "User Doesn't Exist!" << endl;
            getscr();
        }
        else
            break;
    }

    // Password Check
    int tries = 3;
    while (tries != 0)
    {
        pass = util::getValidatedPassword();
        if (!user->passCheck(pass))
        {
            tries -= 1;
            cerr << "Wrong Password!" << endl;
            cerr << tries << " tries left!" << endl;
        }
        else
        {
            // login success
            cout << "Login Successfull." << endl;
            getscr();
            return user;
        }
    }
    // login fail
    cout << "Login Failed." << endl;
    getscr();
    return nullptr;
}

void userDetails(User *usr)
{
    clrscr();
    cout << "___________________________________________" << endl;
    cout << "||              User Details             ||" << endl;
    cout << "```````````````````````````````````````````" << endl;
    cout << "\nName: " << usr->getUserName() << endl;
    cout << "Email: " << usr->getEmail() << endl;
    cout << "Phone: " << usr->getPhoneNum() << endl;
    cout << "Address: " << usr->getAddress() << endl;
    cout << "DOB: " << usr->getDOB() << endl;
    cout << "\n___________________________________________" << endl;
    getscr();
    clrscr();
}

int createNewAccount(User* us){
    str type = getValidatedAccType();
    if(!(Account::loadAccByType(us->userID, type) == nullptr)){
        cerr << "\nUser already has a " << type << " account!" << endl;
        getscr();
        return -1;
    }
    Account* acc = Account::createAcc(us->userID, type);
    cout << type <<" Account Created!" << endl;
    getscr();
    return acc->ID;
}

int loadAccount(User* us){
    int choice;
    while(true)
    {
        clrscr();
        std::cout << "___________ Load A/C _____________" << std::endl;
        cout << "\n1. Load by Type" << endl;
        cout << "2. Load by A/C Number" << endl;
        cout << "3. Back" << endl;
        cout << "\nEnter Your Choice: ";
        choice = getValidatedInt(1,3);
        if(choice == 1){
            
            str type = getValidatedAccType();
            if(type == "Back"){
                continue;
            }
            Account* acc = Account::loadAccByType(us->userID, type);
            if(acc == nullptr){
                cout << "You don't have a "<< type << " account!" << endl;
                cout << "Try Again." << endl;
                getscr();
                continue;
            }
            else{
                cout << "Account Loaded!" << endl;
                getscr();
                return acc->ID;
            }

        }
        else if(choice ==2){
            clrscr();
            int id;
            std::cout << "___________ Load A/C _____________" << std::endl;

            cout << "\nEnter Account Number: ";
            cin >> id;
            Account* acc = Account::loadAcc(id);
            if(acc == nullptr){
                cout << "\nInvalid Account ID!"<< endl;
                cout << "Try Again." << endl;
                getscr();
                continue;
            }
            else{
                cout << "\nAccount Loaded!" << endl;
                getscr();
                return acc->ID;
            }
        }
        else if(choice == 3){
            return -1;
        }
    }
    return -1;
}

int userMenu(User *user){
    while (true)
    {
        clrscr();
        cout<< " _______________________________" << endl;
        cout<< "[__________ USER MENU __________]\n" << endl;
        cout<< "1. Create Account" << endl;
        cout<< "2. Load Account" << endl;
        cout<< "3. User Details" << endl;
        cout<< "4. Back" << endl;

        cout << "\nEnter Your Choice: ";
        int choice = getValidatedInt(1,4);
        int id = -1;

        switch (choice)
        {
        case 1:
            id = createNewAccount(user);
            if(id == -1){
                break;
            }
            cout << "Your Account ID is " << id << endl;
            cout << "Switching to Accounting Menu..." << endl;
            getscr();
            return id;
            break;
        case 2:
            cout << "Loading Account...\n" << endl;
            id = loadAccount(user);
            if( id != -1){
                cout << "Switching to Accounting Menu..."<< endl;
                return id;
            }
            break;
        case 3:
            userDetails(user);
            break;
        case 4:
            cerr << "Switching to Main Menu..." << endl;
            getscr();
            return -1;
        }

    }
    
}

int accountingMenu(int id){
    int choice;
    double amt;
    Account* acc = Account::loadAcc(id);
    while (choice != 6)
    {
        clrscr();
        cout << "_________________ "<< acc->getaccType() <<" Account _________________\n" << endl;
        cout << "1. Deposite" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Transfer" << endl;
        cout << "4. Current Balance" << endl;
        cout << "5. Account History" << endl;
        cout << "6. Back" << endl;
        cout << "\nEnter Your Choice: ";
        choice = getValidatedInt(1,6);
        clrscr();
        switch (choice)
        {
        case 1:
            cout << "__ _ _ _ _ _ Deposite Screen _ _ _ _ _ __\n" << endl;
            cout << "Enter ammount: ";
            amt = getValidatedDouble();
            if(Transactions::deposit(acc, amt)){
                cout << "\nDeposite of " << parseCurrency(amt) << " Successful! :)" << endl;
            }   else cout << "Deposite Failed! :(" << endl;
            cout << "_________________________________________\n" << endl; 
            getscr();
            break;
            
        case 2:
            cout << "__ _ _ _ _ _ Withdrawal Screen _ _ _ _ _ __\n" << endl;
            cout << "Enter ammount: ";
            amt = getValidatedDouble();
            if(Transactions::withdraw(acc, amt)){
                cout << "\nWithdrawal of " << parseCurrency(amt) << " Successfull :)" << endl;
            }   else
            {
            cout << "Withdrawal Failed!"<< endl;
            cout << "Insuffecient Funds! :("<< endl;
            }
            cout << "___________________________________________\n" << endl;
            getscr();
            break;

        case 3:
            int id;
            cout << "__ _ _ _ _ _ Transfer Screen _ _ _ _ _ __\n" << endl;
            cout << "Enter A/C No of receiver's Account: ";
            cin >> id;
            if(Account::loadAcc(id) == nullptr){
                cerr << "Invalid A/C No!" << endl;
                cerr << "Try Again." << endl;
                getscr();
                break;
            }
            cout << "\nEnter ammount: ";
            amt = getValidatedDouble();
            if(Transactions::transferTo(acc, Account::loadAcc(id), amt)){
                cout << "\nTranfer of " << parseCurrency(amt) << " to, A/C No: " << std::to_string(id) << ", was Successful." << endl;
            } else{
            cout << "Transfer failed!" << endl;
            cout << "Insuffecient Funds :(" << endl;
            }
            cout << "___________________________________________\n" << endl;
            getscr();
            break;

        
        case 4:
            cout << "__ _ _ _ _ _ Current Balance _ _ _ _ _ __\n" << endl;
            cout << "Account No: "<< acc->ID << endl;
            cout << "Amount: " << parseCurrency(acc->getBalance()) << endl;
            cout << "_________________________________________\n" << endl; 
            getscr();
            break;
            
        case 5:{
            cout << "__ _ _ _ _ _ Account History _ _ _ _ _ __\n" << endl;
            const auto& history = acc->getHistory();
            for (const auto& entry : history) {
                std::cout << "> "<< entry << std::endl;
            }
            cout << "_________________________________________\n" << endl;
            getscr();
            break;
        }
        case 6:
            cout << "\nExiting..." << endl;
            getscr();
            break;
            return 1;
        }
    }    
}

int main()
{
    int choice, state = 1;
    // Loadind All Users and Accounts
    if(load() == -1){
        cout << "Fix the file Path!" << endl;
        getscr();
        return -1;
    }

    while (state != 0)
    {
        choice = main_menu();
        switch (choice)
        {
        case 1:
        {
            cout << "Switching to Registeration Panel..." <<endl;
            getscr();
            User *usr = registeration();
            cout << "You are now a User. Your credentials are as following:-" << endl;
            getscr();
            userDetails(usr);
            break;
        }
        case 2:
        {
            User *user = login();
            if (user != nullptr)
            {
                int accid;
                while(true){
                    cout << "Switching to the User Menu..." << endl;
                    getscr();
                    accid = userMenu(user);
                    if(accid != -1){
                        accountingMenu(accid);
                    } else break;
                }
            }
            break;
        }
        case 3:
            cout << "Exiting..." << endl;
            state = 0;
            break;
        }
    }
    // Saving All Users and Accounts
    save();

    cout << "\n\n*Press Enter to Close the BMS*.";
    getscr();

    return 0;
}