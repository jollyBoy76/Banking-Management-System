#include "menu.h"
#include <iostream>

int main()
{
    Menu menu; // Menu class deceleration

    std::cout << "Starting BMS...\n"
              << std::endl;
    menu.run(); // Executing menu which contains all the other features
    std::cout << "\n...BMS Stopped" << std::endl;

    std::cout << "Press Enter to close the Window.";
    std::cin.ignore(); // ignore leftover input
    std::cin.get();    // wait for user to press Enter
    return 0;
}