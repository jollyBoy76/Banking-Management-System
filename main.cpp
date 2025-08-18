#include "menu.h"
#include "util.h"
#include <iostream>

int main()
{
    Menu menu; // Menu class deceleration

    std::cout << "Starting BMS...\n"
              << std::endl;
    menu.run(); // Executing menu which contains all the other features
    std::cout << "\n...BMS Stopped" << std::endl;

    std::cout << "Press Enter to close the Window.";
    util::getscr();
    return 0;
}