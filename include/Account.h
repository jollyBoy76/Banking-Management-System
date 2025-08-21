#ifndef ACCOUNT_H
#define ACCOUNT_H

// #include <iostream>
#include <string>
#include <unordered_map>

typedef std::string str;

class Account
{
private:
    static int next_id;                               // holds next id available
    static std::unordered_map<int, Account> accounts; // contains a map to store account objects with repective IDs

public:
    const int ID;

private:
    // Fields
    str username;
    double balance;
    str email;
    str phoneNum;
    str address;
    str DOB;

private:
    // Constructor
    Account(int id, str nm, double bal, str email, str phn, str add, str dob );

// Methpds
public:
    // getters
    str getUserName() const;
    str getEmail() const;
    str getPhoneNum() const;
    str getAddress() const;
    str getDOB() const;
    double getBalance() const;

    // setters
    void setUserName(const str name);
    void setEmail(const str name);
    void setPhoneNum(const str name);
    void setAddress(const str name);
    void setDOB(const str name);
    void setBalance(double bal);

    // Constructor methods which will be used instead of default constructor
    static Account *createAcc(str nm, str email, str phn, str add, str dob ); // returns a pointer to a new object (Dynamic Memory Alloc)
    static Account *signInAcc(int id);             // returns a pointer to object with given id

    // Save Methods
    static void saveToFile(const str &filename);
    static void loadFromFile(const str &filename);
};

// I'm free of this curse now... Let it be here as a remembrance of my sufferings
// int Account::next_id = 1;

#endif