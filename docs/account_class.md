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
| **userID** | const | private | int |
| **balance** | N/A | private | double |

## Methods

-   `createAcc( string nm, double baln )`:    returns a new object address
-   `loadAcc( int id )`:  returns the previously created object's address
-   **getters**
    -   `double getBalance() const`
-   **setters**
    -   `void setBalance(double bal)`
-   `saveAccountsToFile(const string& filename)`:     saves the accounts map into the given file
-   `loadAccountsFromFile(const string& filename)`:   loads the data into accounts map from the given file
-   `findByUserId()`:                                 return a vector of pointers to all related acc to uid 
-   `getUser()`:                                      return a pointer to user(object) related to the acc 

## Functionality of each method

1.  `createAcc()` takes userID as input and create a account with a sequencialy generated ID. Created account object is alloacted in stack, which is temperary. Because this method also stores the created object into *accounts* and returns a pointer pointing to the object in map which itself is dynamically allocated.

2. `loadAcc()` finds a existing account object by its ID and returns a pointer to it. or return nullptr if the account was not found.

3. `saveAccountsToFile()` saves the running state data within *accounts* (unordered_map) into the filename givenn as argument.

4. `loadAccountsFromFile()` loads the data from given filename into *accounts* (unordered_map) and recreates all the Account objects in the map.

5. `findByUserId()` loops through accounts map to store all accounts with the given uid to a vector and returns that vector.

6. `getUser()` return the user object related to the account it is called from.