#include <iostream>
#include <thread>
#include <chrono>

#include "cobra_db.h"

int main() {
    for (int i = 0, c = 0; i < 50; ++i, ++c) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("clear");

        if (c == 0) {
            std::cerr << "**** Starting data base ****";
        }
        else if (c == 1) {
            std::cerr << ".*** Starting data base ****";
        }
        else if (c == 2){
            std::cerr << "*.** Starting data base ****";
        }
        else if (c == 3){
            std::cerr << "**.* Starting data base ****";
        }
        else if (c == 4){
            std::cerr << "***. Starting data base ****";
        }
        else if (c == 5){
            std::cerr << "**** Starting data base .***";
        }
        else if (c == 6){
            std::cerr << "**** Starting data base *.**";
        }
        else if (c == 7){
            std::cerr << "**** Starting data base **.*";
        }
        else if (c == 8){
            std::cerr << "**** Starting data base ***.";
        }
        
        
        if (c == 8) { c = 0; }
    }
    system("clear");
    
    struct stat info;
    
    std::cout << "1.Create data base:" << std::endl
                << "2.Open data base: " << std::endl;

    int command;
    std::cin >> command;
    std::string path;

    while(true) {
        if (0 == command) {
            return 0;
        }
        else if (1 == command) {
            std::cout << "directory: ";
            std::cin >> path;

            if (!stat(path.c_str(), &info)) {
                std::cout << "directory '" << path << "' already exist" << std::endl;
            }
            else {
                mkdir(path.c_str(), 0777);
                std::cout << "created new data base '" << path << "'" << std::endl;
                break;
            }
        }
        else if (2 == command) {
            std::cout << "directory: ";
            std::cin >> path;

            if (stat(path.c_str(), &info)) {
                std::cout << "directory '" << path << "' is not exist" << std::endl;
            }
            else {
                break;
            }
        }
        else {
            std::cout << "try again: ";
            std::cin >> command;
        }
    }
    
    cobra::data_base mybase(path);

    do {
        std::string command;
        std::getline(std::cin, command);

        if (command == "EXIT") {
            break;
        }

        mybase.db_call(command);

    } while (true);
    
    return 0;
}