#include "help.h"
#include<fstream>
#include<string>

void help::help(){
    std::ifstream file("data/help/help.txt");
    if(!file.is_open()){
        std::cerr << "file not open!";
        return ;
    }

    std::cout << "[ _ _ _ _ _ HELP _ _ _ _ _ ]" << std::endl;

    std::string line;
    while (getline(file, line))
    {
        std::cout << line << std::endl;
    }
    std::cout << "- - - - - - - - - - - - - - - " << std::endl;
}
void help::getacchelp(){
    std::ifstream file("data/help/account_help.txt");
    if(!file.is_open()){
        std::cerr << "file not open!";
        return ;
    }

    std::cout << "[ _ _ _ _ _ A/C HELP _ _ _ _ _ ]" << std::endl;

    std::string line;
    while (getline(file, line))
    {
        std::cout << line << std::endl;
    }
    std::cout << "- - - - - - - - - - - - - - - " << std::endl;
}
void help::getuserhelp(){
    std::ifstream file("data/help/user_help.txt");
    if(!file.is_open()){
        std::cerr << "file not open!";
        return ;
    }

    std::cout << "[ _ _ _ _ _ USER HELP _ _ _ _ _ ]" << std::endl;

    std::string line;
    while (getline(file, line))
    {
        std::cout << line << std::endl;
    }
    std::cout << "- - - - - - - - - - - - - - - " << std::endl;
}