#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>

#include "db_impl.h"

/*instructions
    //CREATE person: age, name
    //INSERT person
    //READ person *
    //READ person ID:1
    //UPDATE person ID:1
    //DELETE person *
    //DELETE person ID:1
    //DROP person
*/

namespace cobra {
class data_base {
public:
    data_base(const std::string& directory) : impl(new _db_implement(directory)) 
    {}

    ~data_base() {
        delete impl;
    }

    void db_call(const std::string& command) {
        if (command.empty()) {
            return;
        }

        std::string _inter_command = command;

        _parser(_inter_command);
    }

private:
    #define CREATE "CREATE"
    #define INSERT "INSERT"
    #define READ "READ"
    #define UPDATE "UPDATE"
    #define DELETE "DELETE"
    #define DROP "DROP"

    void _parser(std::string command_line) {
        std::string _command;

        int symbols_c = 0;
        for (int i = 0; (command_line[i] != ' ') && (command_line[i] != '\0'); ++i) {
            _command += command_line[i];

            ++symbols_c;
        }

        auto _check_args = [&]() {
            if (command_line.size() == _command.size()) {
                std::cout << "*missing arguments for '" << _command << "' function" << std::endl;
                return false;
            }
            else {
                command_line.erase(command_line.begin(), command_line.begin() + symbols_c);
                return true;
            }

            return true;
        };
        
        if (_command == CREATE) {
            if (_check_args()) {
                impl->create(command_line);
            }
        }
        else if (_command == INSERT) {
            if (_check_args()) {
                impl->insert(command_line);   
            }
        }
        else if (_command == READ) {
            if (_check_args()) {
                impl->read(command_line);   
            }
        }
        else if (_command == UPDATE) {
            if (_check_args()) {
                impl->update(command_line);   
            }
        }
        else if (_command == DELETE) {
            if (_check_args()) {
                impl->delete_(command_line);   
            }
        }
        else if (_command == DROP) {
            if (_check_args()) {
                impl->drop(command_line);   
            }
        }
        else {
            std::cout << "*command '" << _command << "' is not exist" << std::endl;
        }
    }

private:
    _db_implement* impl;
};
}
