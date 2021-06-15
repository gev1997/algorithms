#include <iostream>
#include <string>
#include <memory>
#include <vector>

using std::shared_ptr;
using std::string;
using std::vector;

struct File {
    File(const string& fname) : file_name(fname)
    {
        prev = nullptr;
        next = nullptr;
    }
    string file_name;
    vector<shared_ptr<File>> files;
    shared_ptr<File> next;
    shared_ptr<File> prev;
};

class fileSystem {
public:
    fileSystem() : root_path("root/"), root(new File(root_path))
    {
        paths.push_back(root_path);
    }

    ~fileSystem() {

    }

    void run_command(const string& input_command) {
        string command;
        string instruction;

        for (int i = 0; i < input_command.size(); ++i) {
            if (input_command[i] == ' ') {
                instruction += string(input_command.begin() + i + 1, input_command.end());
                break;
            }

            command += input_command[i];
        }

        //cd
        if (command == "cd") {
            if (instruction == "..") {
                if (root->prev != nullptr) {
                    root = root->prev;
                    paths.pop_back();
                }
            }
            else {
                bool is_exist = false;
                for (int i = 0; i < root->files.size(); ++i) {
                    if (root->files[i]->file_name == instruction) {
                        is_exist = true;
                    }
                }

                if (!is_exist) {
                    std::cout << "No such file or directory." << std::endl;
                }
                else {
                    for (int i = 0; i < root->files.size(); ++i) {
                        if (root->files[i]->file_name == instruction) {
                            root->files[i]->prev = root;
                            root = root->files[i];
                            break;
                        }
                    }

                    paths.push_back(string(instruction + '/'));
                }
            }
        }

        //mkdir
        else if (command == "mkdir") {
            bool is_not_exist = true;
            for (int i = 0; i < root->files.size(); ++i) {
                if (root->files[i]->file_name == instruction) {
                    std::cout << "File " << instruction << " already exists.";
                    is_not_exist = false;
                }
            }

            if (is_not_exist) {
                root->files.push_back(new File(instruction));
                root->files.back()->prev = root;
            }
        }

        //ls
        else if (command == "ls") {
            for (int i = 0; i < root->files.size(); ++i) {
                std::cout <<  root->files[i]->file_name << ' ';
            }
        }

        //pwd
        else if (command == "pwd") {
            for (auto i : paths) {
                std::cout << i;
            }

            std::cout << std::endl;
        }
    }

private:
    vector<string> paths;
    string root_path;
    File* root;
};

int main() {
    fileSystem obj;

    do {
        string command;
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        obj.run_command(command);
    } while(true);

    return 0;
}
