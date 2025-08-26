#ifndef USER_H
#define USER_H

//includes
#include<string>
#include<unordered_map>
#include<vector>
#include"util.h"

typedef std::string str;

struct UserData{
    str name, email, phone, add, dob; 
};

//forward decleration
class Account;


class User{

private:
    static int next_userid;
    static std::unordered_map<int, User> users;
    static std::unordered_map<int, str> passwords;

public:
    const int userID;

private:
    str username,email,phoneNum,address,DOB;
    str password;

private:
    User(int uid, str name, str email, str phn, str add, str dob);

public:

    // getters
    str getUserName() const;
    str getEmail() const;
    str getPhoneNum() const;
    str getAddress() const;
    str getDOB() const;

    // setters
    void setUserName(const str name);
    void setEmail(const str eml);
    void setPhoneNum(const str phn);
    void setAddress(const str add);
    void setDOB(const str dob);
    
    void createPassword();

    bool passCheck(str pass);

    static User* createUser(str name, str email, str phn, str add, str dob);
    
    static User* createUser(const UserData &ud);

    static User* loadUserByUID(int uid);

    static User* loadByUsername(const str& username);

    static void loadUsersFromFile(const str filename);
    static void loadPasswordsFromFile(const str filename);
    
    static void saveUsersToFile(const str filename);
    static void savePasswordsToFile(const str filename);

    //returns all accounts belonging to a user
    std::vector<Account*> getAccounts();

};


#endif