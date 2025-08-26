#include "user.h"
#include "account.h"
#include "util.h"
#include <fstream>
#include <iostream>

//Construtor
User::User(int uid, str name, str email, str phn, str add, str dob)
    : userID(uid), username(name), email(email), phoneNum(phn), address(add), DOB(dob){}


// Getters
str User::getUserName() const
{
    return username;
}
str User::getEmail() const
{
    return email;
}
str User::getPhoneNum() const
{
    return phoneNum;
}
str User::getAddress() const
{
    return address;
}
str User::getDOB() const
{
    return DOB;
}

// Settres
void User::setUserName(const str name)
{
    username = name;
}
void User::setEmail(const str eml)
{
    email = eml;
}
void User::setPhoneNum(const str phn)
{
    phoneNum = phn;
}
void User::setAddress(const str add)
{
    address = add;
}
void User::setDOB(const str dob)
{
    DOB = dob;
}

// Public Constructor
User* User::createUser(str name, str email, str phn, str add, str dob){
    users.emplace(next_userid, User(next_userid, name, email, phn, add, dob));
    int current_userid = next_userid;
    next_userid++;
    return &users.at(current_userid);
}
// Overloades constuctor
User* User::createUser(const UserData &ud){
    users.emplace(next_userid, User(next_userid, ud.name, ud.email, ud.phone, ud.add, ud.dob));
    int current_userid = next_userid;
    next_userid++;
    return &users.at(current_userid);
}

// Find User By ID
User* User::loadUserByUID(int uid){
    auto it = users.find(uid);
    if (it != users.end()){
            return &it->second;
    } else return nullptr;
}

// Fine by Username
User* User::loadByUsername(const str& username) {
    for (auto& pair : users) {
        if (pair.second.getUserName() == username) {
            return &pair.second;
        }
    }
    return nullptr;  // Not found
}

// Save Methods
void User::loadUsersFromFile(const str filename){
    std::ifstream file(filename); // 1. Open file for reading
    if (!file.is_open())
        return; // 2. Check if file exists

    str line; // a variable to store the current line
    int max_id = 0;   // stores the maximum id to avoid overwriting

    while (std::getline(file, line))
    {

    unsigned int pos1 = line.find(';');           // 1st comma
    unsigned int pos2 = line.find(';', pos1 + 1); // 2nd comma
    unsigned int pos3 = line.find(';', pos2 + 1); // 3rd comma
    unsigned int pos4 = line.find(';', pos3 + 1); // 4th comma
    unsigned int pos5 = line.find(';', pos4 + 1); // 5th comma

    // Parse all fields from the line
    int uid = std::stoi(line.substr(0, pos1));
    str user = line.substr(pos1 + 1, pos2 - pos1 - 1);
    str email = line.substr(pos2 + 1, pos3 - pos2 - 1);
    str phn = line.substr(pos3 + 1, pos4 - pos3 - 1);
    str add = line.substr(pos4 + 1, pos5 - pos4 - 1);
    str dob = line.substr(pos5 + 1); // Last field, no end position needed

    users.emplace(uid, User(uid, user, email, phn, add, dob));
        max_id = std::max(max_id, uid);
    }
    next_userid = max_id + 1;
    file.close();
}

void User::saveUsersToFile(const str filename){
    std::ofstream file(filename);
    for (const auto &pair : users)
    {
        const User &usr = pair.second;
        file << usr.userID << ';' << usr.getUserName() << ';' << usr.getEmail() << ';' << usr.getPhoneNum() << ';' << usr.getAddress() << ';' << usr.getDOB() << "\n";
    }
    file.close();
}

// Accounts related to this User
std::vector<Account*> User::getAccounts() {
    return Account::findByUserID(this->userID);
}

// Password
void User::createPassword(){
    this->password = util::getValidatedPassword();
    passwords.emplace(userID, this->password);
}

bool User::passCheck(str pass){
    if (passwords[this->userID] == pass){
        return true;
    } else return false;
}

void User::loadPasswordsFromFile(const str filename){
    std::ifstream file(filename); // 1. Open file for reading
    if (!file.is_open())
        return; // 2. Check if file exists

    str line;

    while(getline(file, line)){
        unsigned int pos1 = line.find(';');           // 1st comma

    int uid = std::stoi(line.substr(0, pos1));
    str pass = line.substr(pos1+1);

    passwords.emplace(uid, pass);                     // updated passwords
    }
    file.close();
}

void User::savePasswordsToFile(const str filename){
      std::ofstream file(filename); // 1. Open file for reading
    if (!file.is_open())
        return; // 2. Check if file exists
    for (auto it = passwords.begin(); it != passwords.end(); ++it) {
        file << it->first << ';' << it->second << std::endl;
    }
    file.close();
    
}

std::unordered_map<int,User> User::users;
std::unordered_map<int,str> User::passwords;
int User::next_userid = 1;