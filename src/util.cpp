#include "util.h"
#include <iostream>
#include <sstream>      //for using "ostringstream"
#include <iomanip>      //for using "setprecision"
#include <cstdlib>      //used to access "system()"
#include <limits>


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
        std::cin.clear();                                                                       // resets error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                     // clears input buffer
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

std::string util::parseCurrency(double amt)
{
    std::string cur = "Rs.";  //selecting currency
    std::ostringstream oss;

    oss << std::fixed << std::setprecision(2) << amt;     //truncates amount to 2 decimal points

    cur.append(oss.str());    //appending truncated amount after string conversion

    return cur;
}

void util::clrscr()
{
    system("cls");
}

void util::getscr()
{
    system("pause > nul");
}