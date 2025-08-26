# User Class: Fields and Methods
---

## Purpose

This class was created to seperated the user details from account detail, to create a logical seperation between a "Person" and an "Account".
Through this we can have multiple accounts tied to a single User. It also makes code less messy as getting all user details in account class with setters and getter made the code too centralized.

What id dose:

-   Create a user object with all user details (like: name, email, phone num, etc).

-   Can be initialized through constructor which taked all details as arguments (strings).

-   assigns each user with a password and make sure they are secured