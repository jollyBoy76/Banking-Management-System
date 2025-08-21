# Account Class: Fiels and Method
---

## Purpose

I've decided to re-create the previously created "Account.class", as it's functionality doesn't fit well within the system. The new Acount class will work on the following priciples:
-   Any and all account info will be non-modifiable without getter and setter methods.
-   It's sole purpose is to return an unique object by either creating or loading a prev created one.
-   Each Object represent an unique account with data memebers as it's details.
-   Each Object will have a "ID" feild as it's unique identification.


## Feilds

The following will be the feilds within the account class:

| Feild | Characteristics | Accessibilty | Data Type |
|----------|:--------:|---------:|---------:|
| **ID** | const | public | int |
| **next_id** | static | private | int |
| **accounts** | static | private | std::unordered_map<int, Account> |
| **username** | N/A | private | string |
| **balance** | N/A | private | double |
|  |  |  |  |

## Methods

-   `createAcc( string nm, double baln )`:    returns a new object address
-   `loadAcc( int id )`:  returns the previously created object's address
-   **getters**
    -   `str getUserName() const`
    -   `double getBalance() const`
-   **setters**
    -   `void setUserName(const str name)`
    -   `void setBalance(double bal)`
-   `saveToFile(const string& filename)`:     saves the accounts map into the given file
-   `loadFromFile(const string& filename)`:   loads the data into accounts map from the given file

## Functionality of each method

1.  `createAcc()` takes username and bank balance as input and create a account with a sequence generate ID. Created account object is alloacted in stack, which is temperary. Because this method also stores the created object into *accounts* and returns a pointer pointing to the object in map which itself is dynamically allocated.

2. `loadAcc()` finds a existing account object by its ID and returns a pointer to it. or return nullptr if the account was not found.

3. `saveToFile()` saves the running state data within *accounts* (unordered_map) into the filename givenn as argument.

4. `loadFromFile()` loads the data from given filename into *accounts* (unordered_map) and recreates all the Account objects in the map.