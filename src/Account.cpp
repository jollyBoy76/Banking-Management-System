// Account class definition
#include "account.h"
#include "user.h"
#include "util.h"
#include <iostream>
#include <fstream>

using std::cout;

// Defining class constructor
Account::Account(int id, int uid, double bal, str tp)
    : ID(id), userID(uid) ,balance(bal) ,type(tp){}

//getters
double Account::getBalance() const
{
    return balance;
}

str Account::getaccType() const
{
    return this->type;
}

int Account::getUserID() const
{
    return userID;
}

//settres
void Account::setBalance(double bal)
{
    if (bal >= 0)
    {
        balance = bal;
    }
}

// Account Object constructor Methods
Account *Account::createAcc(int uid, str type)
{
    double bal = 0.0;
    str tp = type;
    accounts.emplace(next_id, Account(next_id, uid, bal, tp));
    int current_id = next_id; // stores the current objects id

    next_id++;
    return &accounts.at(current_id); // returns address of aobject at current_id
}

// Account Object Loader Method
Account *Account::loadAcc(int id)
{
    auto it = accounts.find(id);
    return ((it != accounts.end()) ? &it->second : nullptr);
}

Account *Account::loadAccByType(int uid, str tp){
    for (auto& pair : accounts) {
        if (pair.second.getUserID() == uid && pair.second.getaccType() == tp) {
            return &pair.second;
        }
    }
    return nullptr;  // Not found
}

// Save Methods

bool Account::loadAccountsFromFile(const str &filename)
{
    std::ifstream file(filename); // 1. Open file for reading
    if (!file.is_open())
        return false; // 2. Check if file exists

    std::string line; // a variable to store the current line
    int max_id = 0;   // stores the max_id to avoid overwriting (source_of_suffering)

    while (std::getline(file, line))
    {

        unsigned int pos1 = line.find(';');           // 1st comma
        unsigned int pos2 = line.find(';' ,pos1 + 1);
        unsigned int pos3 = line.find(';', pos2 + 1);

        // Parse all fields from the line
        int id = std::stoi(line.substr(0, pos1));
        int uid = std::stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        double balance = std::stod(line.substr(pos2 + 1, pos3 - 1));
        str type = line.substr(pos3+1);

        accounts.emplace(id, Account(id, uid, balance, type));
        max_id = std::max(max_id, id);
    }
    next_id = max_id + 1;
    file.close();
    return true;
}

bool Account::saveAccountsToFile(const str &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false; // 2. Check if file exists
    for (const auto &pair : accounts)
    {
        const Account &acc = pair.second;
        file << acc.ID << ';' << acc.getUserID() << ';' << acc.getBalance() << ';' << acc.getaccType() << "\n";
    }
    file.close();
    return true;
}

// Account relationship methods

// To return a vector containing accounts with same user id
std::vector<Account*> Account::findByUserID(int uid)
{
    std::vector<Account*> userAccounts;
    for (auto& pair : accounts)
    {
        if (pair.second.userID == uid)
        {
            userAccounts.push_back(&pair.second);
        }
    }
    return userAccounts;
}

// To get the user(object) related to this accouns
User* Account::getUser()
{
    return User::loadUserByUID(this->userID);
}

// History Manip
// Adding str to vector
void Account::addHistory(const std::string& entry) {
    history.push_back(entry);
}
// gets history(vector)
const std::vector<std::string>& Account::getHistory() const {
    return history;
}

//Save History
bool Account::saveHistoryToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open())
        return false; // 2. Check if file exists
    for (const auto& entry : history) {
        file << entry << "\n";
    }
    return true;
}

//Load history
bool Account::loadHistoryFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        return false; // 2. Check if file exists
    std::string line;
    history.clear();    //Clears current history (might come back to bite me in neck)
    while (std::getline(file, line)) {
        history.push_back(line);
    }
    return true;
}


// staic member definition
std::unordered_map<int, Account> Account::accounts;
int Account::next_id = 1;
