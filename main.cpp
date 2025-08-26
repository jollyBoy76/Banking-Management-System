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
    flag1 = User::loadUsersFromFile("C:/Users/Lnovo/Documents/C++/Projects/Banking_Management_System/data/users.txt");
    
    flag2 = User::loadPasswordsFromFile("C:/Users/Lnovo/Documents/C++/Projects/Banking_Management_System/data/passwords.txt");
    flag3 = Account::loadAccountsFromFile("C:/Users/Lnovo/Documents/C++/Projects/Banking_Management_System/data/accounts.txt");
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
    flag1 = User::saveUsersToFile("C:/Users/Lnovo/Documents/C++/Projects/Banking_Management_System/data/users.txt");
    flag2 = User::savePasswordsToFile("C:/Users/Lnovo/Documents/C++/Projects/Banking_Management_System/data/passwords.txt");
    flag3 = Account::saveAccountsToFile("C:/Users/Lnovo/Documents/C++/Projects/Banking_Management_System/data/accounts.txt");
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
    cout << "__Main Menu__" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;

    cout << "Your Choice: ";
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
    cout << "-------Printing User Details-------" << endl;
    cout << "Name: " << usr->getUserName() << endl;
    cout << "Email: " << usr->getEmail() << endl;
    cout << "Phone: " << usr->getPhoneNum() << endl;
    cout << "Address: " << usr->getAddress() << endl;
    cout << "DOB: " << usr->getDOB() << endl;
    cout << "-----------------------------------" << endl;
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
        cout << "1. Load by Type" << endl;
        cout << "2. Load by ID" << endl;
        cout << "3. Back" << endl;
        cout << "\nEnter Your Choice: ";
        choice = getValidatedInt(1,3);
        if(choice == 1){
            str type = getValidatedAccType();
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
            int id;
            cout << "Enter Account ID: ";
            cin >> id;
            Account* acc = Account::loadAcc(id);
            if(acc == nullptr){
                cout << "Invalid Account ID!"<< endl;
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
        cout<< "1. Create Account" << endl;
        cout<< "2. Load Account" << endl;
        cout<< "3. Back" << endl;

        cout << "Enter Your Choice: ";
        int choice = getValidatedInt(1,3);
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
            cerr << "Switching to Main Menu..." << endl;
            getscr();
            return -1;
        }

    }
    
}

void accountingMenu(int id){
    int choice;
    double amt;
    Account* acc = Account::loadAcc(id);
    while (choice != 5)
    {
        clrscr();
        cout << "1. Deposite" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Current Balance" << endl;
        cout << "4. Account History" << endl;
        cout << "5. Back" << endl;
        cout << "\nEnter Your Choice: ";
        choice = getValidatedInt(1,5);
        switch (choice)
        {
        case 1:
            cout << "__ _ _ _ _ _ Deposite Screen _ _ _ _ _ __\n" << endl;
            cout << "Enter ammount: ";
            amt = getValidatedDouble();
            if(Transactions::deposit(acc, amt)){
                cout << "Deposite Successful! :)" << endl;
            }   else cout << "Deposite Failed! :()" << endl;
            cout << "_________________________________________\n" << endl; 
            getscr();
            break;
            
        case 2:
            cout << "__ _ _ _ _ _ Withdrawal Screen _ _ _ _ _ __\n" << endl;
            cout << "Enter ammount: ";
            amt = getValidatedDouble();
            if(Transactions::withdraw(acc, amt)){
                cout << "Withdrawal Successfull!" << endl;
            }   else
            {
            cout << "Withdrawal Failed! :)"<< endl;
            cout << "Insuffecient Funds! :("<< endl;
            }
            cout << "___________________________________________\n" << endl;
            getscr();
            break;
        
        case 3:
            cout << "__ _ _ _ _ _ Current Balance _ _ _ _ _ __\n" << endl;
            cout << "Amount: " << parseCurrency(acc->getBalance()) << endl;
            cout << "_________________________________________\n" << endl; 
            getscr();
            break;
            
        case 4:{
            cout << "__ _ _ _ _ _ Account History _ _ _ _ _ __\n" << endl;
            const auto& history = acc->getHistory();
            for (const auto& entry : history) {
                std::cout << "> "<< entry << std::endl;
            }
            cout << "_________________________________________\n" << endl;
            getscr();
            break;
        }
        case 5:
            cout << "Exiting..." << endl;
            getscr();
            break;
        
        default:
            break;
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
                cout << "Switching to the User Menu..." << endl;
                getscr();
                int accid = userMenu(user);
                if(accid != -1){
                    accountingMenu(accid);
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