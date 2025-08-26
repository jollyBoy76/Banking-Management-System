#include "util.h"
#include <iostream>
#include <sstream> //for using "ostringstream"
#include <iomanip> //for using "setprecision"
#include <cstdlib> //used to access "system()"
#include <limits>
#include <regex>
#include <ctime>

int util::getValidatedInt(int min, int max)
{
    int amt;
    while (true)
    {
        std::cin >> amt;
        if (!std::cin.fail() && amt >= min && amt <= max)
        { // only runs if the input is safe
            return amt;
        }
        std::cin.clear();                                                                         // resets error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                       // clears input buffer
        std::cout << "Invalid input! \nEnter a number between " << min << " and " << max << ": "; // prints error message
    }
}

double util::getValidatedDouble()
{
    double value;
    while (true)
    {
        std::cin >> value;
        if (!std::cin.fail())
        { // cin.fail() checks if the input hased failed or not
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! \nEnter a valid double: ";
    }
}

str util::getValidatedEmail()
{
    util::clearInputBuffer();
    std::regex emailPattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    str email;

    while (true)
    {
        clrscr();
        std::cout << "Enter your email: ";
        std::getline(std::cin, email);

        if (std::regex_match(email, emailPattern))
        {
            std::cout << "Email accepted!" << std::endl;
            getscr();
            return email; // valid email
        }
        else
        {
            std::cout << "Invalid email format. Try again.\n";
            getscr();
        }
    }
}

str util::getValidatedAddress()
{
    util::clearInputBuffer();
    std::regex addressPattern(R"(^([A-Za-z0-9\s]+),\s*([A-Za-z\s]+),\s*([A-Z]+)$)");
    str add;
    while (true)
    {
        clrscr();
        std::cout << "Enter your Address: ";
        getline(std::cin, add);

        if (std::regex_match(add, addressPattern))
        {
            std::cout << "Address accepted!" << std::endl;
            getscr();
            return add; // valid address
        }
        else
        {
            std::cout << "Invalid Address format.\nFormat: [Rps more, Danapur, PATNA] \nTry again.\n";
            getscr();
        }
    }
}

str util::getValidatedDOB()
{
    util::clearInputBuffer();
    std::string dob;
    std::regex pattern(R"(^(\d{2})/(\d{2})/(\d{4})$)");
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (true)
    {
        clrscr();
        std::cout << "Enter DOB (DD/MM/YYYY): ";
        std::cin >> dob;

        std::smatch match;
        if (std::regex_match(dob, match, pattern))
        {
            int day = std::stoi(match[1]);
            int month = std::stoi(match[2]);
            int year = std::stoi(match[3]);

            if (year >= 1900 && year <= 2025 &&
                month >= 1 && month <= 12 &&
                day >= 1 && day <= daysInMonth[month])
            {
                std::cout << "DOB accepted!" << std::endl;
                getscr();
                return dob; // valid
            }
        }
        std::cout << "Invalid DOB. Try again.\n";
        getscr();
    }
}

str util::getValidatedAccType(){
    str types[2] = {"Current","Saving"};
    std::cout << "1. Current" << std::endl;
    std::cout << "2. Saving" << std::endl;
    std::cout << "\nEnter your Choice: ";
    int ch = util::getValidatedInt(1,2);
    return types[ch-1];
}

bool util::isValidPassword(const str &password)
{
    if (password.length() < 8)
        return false;

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;

    for (char ch : password)
    {
        if (std::islower(ch))
            hasLower = true;
        else if (std::isupper(ch))
            hasUpper = true;
        else if (std::isdigit(ch))
            hasDigit = true;
        else
            hasSpecial = true; // any non-alphanumeric char
    }

    return hasLower && hasUpper && hasDigit && hasSpecial;
}

str util::getValidatedPassword()
{
    util::clearInputBuffer();
    str password;
    while (true)
    {
        clrscr();
        std::cout << "Enter password: ";
        std::getline(std::cin, password);

        if (isValidPassword(password))
        {
            std::cout << "Password Entry Accepted!\n";
            getscr();
            clrscr();
            return password;
        }
        else
        {
            std::cout << " Invalid password. Requirements:\n"
                      << " - At least 8 characters\n"
                      << " - At least 1 lowercase letter\n"
                      << " - At least 1 uppercase letter\n"
                      << " - At least 1 digit\n"
                      << " - At least 1 special character\n\n";
            getscr();
        }
    }
}

str util::getValidatedName()
{
    util::clearInputBuffer();
    str name;
    while (true)
    {
        int temp = 1;
        clrscr();
        std::cout << "Enter Your Full Name: ";
        getline(std::cin, name);
        if (name == "")
        {
            std::cerr << "Name can not be empty!\n"
                      << std::endl;
            getscr();
            continue;
        }
        for (char c : name)
        {
            if (std::isdigit(c))
            {
                std::cerr << "Name can not contain a number!\n"
                          << std::endl;
                temp = 0;
                getscr();
                break;
            }
        }
        if (temp == 1)
        {
            // std::cout << "Name Accepted!\n"
            //           << std::endl;
            // getscr();
            clrscr();
            return name;
        }
    }
}

str util::getValidatedPhoneNum()
{
    util::clearInputBuffer();
    str phn;

    while (true)
    {
        int temp = 1;
        clrscr();
        std::cout << "Enter Your Phone Number: ";
        getline(std::cin, phn);

        for (char c : phn)
        {
            if (!std::isdigit(c))
            {
                std::cerr << "Can't contain Alphabet!" << std::endl;
                temp = 0;
                getscr();
                break;
            }
        }
        if (phn.length() < 10)
        {
            std::cerr << "Too few digits!" << std::endl;
            getscr();
            continue;
        }
        if (phn.length() > 10)
        {
            std::cerr << "Too many digits!" << std::endl;
            getscr();
            continue;
        }
        if (temp == 1)
        {
            std::cout << "Phone Number Accepted!" << std::endl;
            getscr();
            clrscr();
            return phn;
        }
    }
}

str util::parseCurrency(double amt)
{
    str cur = "Rs."; // selecting currency
    std::ostringstream oss;

    oss << std::fixed << std::setprecision(2) << amt; // truncates amount to 2 decimal points

    cur.append(oss.str()); // appending truncated amount after string conversion

    return cur;
}

str util::getTimeAndDate(){
    str date_time;
    // current time as something :/, i don't get it al
    std::time_t now = std::time(nullptr);

    // Convert to simple time and date :)
    std::tm* local_time = std::localtime(&now);

    // Storing as a ostringstream object
    std::ostringstream oss;

    oss << std::put_time(local_time, "%I:%M %p, %d %B %Y");

    //storing oss in string
    date_time = oss.str();

    return date_time;
}

void util::clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void util::clrscr()
{
    system("cls");
}

void util::getscr()
{
    system("pause > nul");
}