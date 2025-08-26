#ifndef ACCOUNT_H
#define ACCOUNT_H

// #include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

typedef std::string str;

class User;

class Account
{
public:
    static int next_id;                               // holds next id available
    static std::unordered_map<int, Account> accounts; // contains a map to store account objects with repective IDs

public:
    const int ID;

private:
    // Fields
    double balance;
    const int userID;
    str type;
    
private:
    // Constructor
    Account(int id, int userID, double bal, str type);

// Methpds
public:
    // getters
    double getBalance() const;
    int getUserID() const;  //returns corresponding userID
    str getaccType() const;

    // setters
    void setBalance(double bal);

    // Constructor methods which will be used instead of default constructor
    static Account *createAcc(int uid, str type); // returns a pointer to a new object (Dynamic Memory Alloc)
    
    static Account *loadAcc(int id);             // returns a pointer to object with given id

    static Account *loadAccByType(int uid, str type);

    // Save Methods
    static void saveAccountsToFile(const str &filename);
    static void loadAccountsFromFile(const str &filename);

    //Returns accounts with same userID (meaning acc created by same user)
    static std::vector<Account*> findByUserID(int uid);

    //History Manipulators '-'
    void addHistory(const std::string& entry);
    const std::vector<std::string>& getHistory() const;

    //History Save and load
    void saveHistoryToFile(const std::string& filename) const;
    void loadHistoryFromFile(const std::string& filename);

    // User getter
    User* getUser();

protected:
    // stores history
    std::vector<std::string> history;
};

// I'm free of this curse now... Let it be here as a remembrance of my sufferings
// int Account::next_id = 1;

#endif