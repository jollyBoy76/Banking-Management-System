// Account class definition
#include "account.h"
#include "util.h"
#include <iostream>
#include <fstream>

using std::cout;

// Defining class constructor
Account::Account(int id, str nm, double bal, str email, str phn, str add, str dob )
    : ID(id), username(nm), balance(bal), email(email), phoneNum(phn), address(add), DOB(dob) {}

// Getters
str Account::getUserName() const
{
    return username;
}
str Account::getEmail() const
{
    return email;
}
str Account::getPhoneNum() const
{
    return phoneNum;
}
str Account::getAddress() const
{
    return address;
}
str Account::getDOB() const
{
    return DOB;
}
double Account::getBalance() const
{
    return balance;
}

// Settres
void Account::setUserName(const str name)
{
    username = name;
}
void Account::setEmail(const str eml)
{
    email = eml;
}
void Account::setPhoneNum(const str phn)
{
    phoneNum = phn;
}
void Account::setAddress(const str add)
{
    address = add;
}
void Account::setDOB(const str dob)
{
    DOB = dob;
}
void Account::setBalance(double bal)
{
    if( bal >=0 )
    {
        balance = bal;
    }
}

// Account Object constructor Methods
Account* Account::createAcc(str nm, str email, str phn, str add, str dob )
{
    double bal = 0.0;
    accounts.emplace(next_id, Account(next_id, nm, bal, email, phn, add, dob));
    int current_id = next_id;      //stores the current objects id
    next_id++;
    return &accounts.at(current_id);    // returns address of aobject at current_id
}

// Account Object Loader Method
Account *Account::signInAcc(int id)
{
    auto it = accounts.find(id);
    return (it != accounts.end()) ? &it->second : nullptr;
}

// Save Methods

void Account::loadFromFile(const str &filename)
{
    std::ifstream file(filename); // 1. Open file for reading
    if (!file.is_open())
        return; // 2. Check if file exists

    std::string line; // a variable to store the current line
    int max_id = 0;   // stores the maximum id to avoid overwriting

    while (std::getline(file, line))
    {

        size_t pos1 = line.find(',');           // 1st comma
    size_t pos2 = line.find(',', pos1 + 1); // 2nd comma
    size_t pos3 = line.find(',', pos2 + 1); // 3rd comma
    size_t pos4 = line.find(',', pos3 + 1); // 4th comma
    size_t pos5 = line.find(',', pos4 + 1); // 5th comma
    size_t pos6 = line.find(',', pos5 + 1); // 6th comma

    // Parse all fields from the line
    int id = std::stoi(line.substr(0, pos1));
    std::string user = line.substr(pos1 + 1, pos2 - pos1 - 1);
    double balance = std::stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
    str email = line.substr(pos3 + 1, pos4 - pos3 - 1);
    str phn = line.substr(pos4 + 1, pos5 - pos4 - 1);
    str add = line.substr(pos5 + 1, pos6 - pos5 - 1);
    str dob = line.substr(pos6 + 1); // Last field, no end position needed

    accounts.emplace(id, Account(id, user, balance, email, phn, add, dob));
        max_id = std::max(max_id, id);
    }
    next_id = max_id + 1;
    file.close();
}

void Account::saveToFile(const str &filename)
{
    std::ofstream file(filename);
    for (const auto &pair : accounts)
    {
        const Account &acc = pair.second;
        file << acc.ID << "," << acc.getUserName() << "," << acc.getBalance() << "," << acc.getEmail() << "," << acc.getPhoneNum() << "," << acc.getAddress() << "," << acc.getDOB() << "\n";
    }
    file.close();
}

// staic member definition
std::unordered_map<int, Account> Account::accounts;
int Account::next_id = 1;