class _db_implement {
public:
    _db_implement(const std::string& directory) : path(directory + "/")
    {}

    void create(std::string command) {        
        std::string base_name = _get_base_name(command);

        if (_check_file_exist(base_name)) {
            std::cout << "*data base '" << base_name << "' already exist" << std::endl;
            return;
        }

        _erase_space_begin(command);

        std::vector<std::string> base_property;
        while (!command.empty()) {
            for (int i = 0; i < command.size(); ++i) {
                if (command[i] == ',') {
                    base_property.push_back(std::string(command.begin(), command.begin() + i));
                    command.erase(command.begin(), command.begin() + i + 1);
                    _erase_space_begin(command);
                    break;
                }
                else if (i == command.size() - 1) {
                    base_property.push_back(std::string(command.begin(), command.begin() + i + 1));
                    command.erase(command.begin(), command.begin() + i + 1);
                    break;
                }
            }
        }
        
        std::ofstream _w_file;
        _w_file.open(path + base_name + ".txt");

        for (int i = 0; i < base_property.size(); ++i) {
            _w_file << base_property[i];
            if (i == base_property.size() - 1) {
                continue;
            }
            _w_file << std::endl;
        }

        _w_file.close();

        std::ofstream _w_file1;
        _w_file1.open(path + base_name + "_table.txt");
        _w_file1.close();
    }

    void insert(std::string command) {
        std::string base_name = _get_base_name(command);

        _erase_space_begin(command);

        if (!_check_file_exist(base_name)) {
            std::cout << "*data base '" << base_name << "' is not exist" << std::endl;
            return;
        }

        std::ifstream _r_file;
        _r_file.open(path + base_name + ".txt"); //read properties
        std::vector<std::string> property;

        while (!_r_file.eof()) {
            std::string line;
            std::getline(_r_file, line);

            property.push_back(line);
        }

        _r_file.close(); //end read properties

        if (property[0].empty()) {
            std::cout << "'" << base_name << "'" << " is empty base" << std::endl;
        }

        std::ofstream _w_file;
        _w_file.open(path + base_name + "_table.txt", std::ios_base::app); //input data

        for (int i = 0; i < property.size(); ++i) { 
            std::string value;
            std::cout << property[i] << ": ";
            std::cin >> value;

            _w_file << property[i] << ":" << value << std::endl;
        }

        _w_file << '-' << std::endl;

        _w_file.close(); //end input data
    }

    void read(std::string command) {
        std::string base_name = _get_base_name(command);
        _erase_space_begin(command);

        if (!_check_file_exist(base_name)) {
            std::cout << "*data base '" << base_name << "' is not exist" << std::endl;
            return;
        }

        if (command.empty()) {
            std::cout << "*missing arguments for function" << std::endl;
        }
        else if (command == "*") {
            std::ifstream _r_file;
            _r_file.open(path + base_name + ".txt"); //read properties

            int property_count = 0;

            std::cout << std::endl;
            for (; !_r_file.eof(); ++property_count) {
                std::string line;
                std::getline(_r_file, line);

                std::cout << line << "  ";
            }
            std::cout << std::endl;

            _r_file.close(); //end read properties

            std::ifstream _r_file1;
            _r_file1.open(path + base_name + "_table.txt"); //read base

            for (int i = 0; !_r_file1.eof(); ++i) {
                std::string line;
                std::getline(_r_file1, line);

                for (int l = 0; l < line.size(); ++l) {
                    if (line[l] == ':') {
                        line.erase(line.begin(), line.begin() + l + 1);
                        break;
                    }
                }

                if (line == "-") { continue; }
                if (i == property_count + 1) { 
                    std::cout << std::endl; 
                    i = 0;
                }
                
                std::cout << line << "  ";
            }
            std::cout << std::endl;

            _r_file1.close(); //end read base
        }
        else if((command.size() >= 2) && (command[0] == 'I') && (command[1] == 'D')) {
            for (int l = 0; l < command.size(); ++l) {
                if (command[l] == ':') {
                    command.erase(command.begin(), command.begin() + l + 1);
                    break;
                }
            }

            _erase_space_begin(command);
            _erase_space_end(command);

            int id = 0;

            try {
                id = std::stoi(command);
                if (id <= 0) {
                    std::cout << "*invalid ID" << std::endl;
                    return;
                }
                --id;
            }
            catch(const std::exception& exc) {
                std::cout << "*invalid ID" << std::endl;
                return;
            }

            
            std::ifstream _r_file;
            _r_file.open(path + base_name + ".txt"); //read properties

            int property_count = 0;

            std::cout << std::endl;
            for (; !_r_file.eof(); ++property_count) {
                std::string line;
                std::getline(_r_file, line); 

                std::cout << line << "  ";
            }
            std::cout << std::endl;

            _r_file.close(); //end read properties         


            std::ifstream _r_file1;
            _r_file1.open(path + base_name + "_table.txt"); //read base
            
            for (int i = 0; i < id * (property_count + 1); ++i) {
                std::string line;
                std::getline(_r_file1, line);                        
            }
            
            for (int i = 0; i < property_count; ++i) {
                std::string line;
                std::getline(_r_file1, line);

                if (line.empty()) {
                    std::cout << "*invalid ID" << std::endl;
                    return;
                }

                for (int l = 0; l < line.size(); ++l) {
                    if (line[l] == ':') {
                        line.erase(line.begin(), line.begin() + l + 1);
                        break;
                    }
                }

                std::cout << line << " ";
            }
            std::cout << std::endl;
            _r_file1.close(); //end read base 
        }
        else {
            std::cout << "*invalid command" << std::endl;
        }
    }

    void update(std::string command) {
        std::string base_name = _get_base_name(command);

        if (!_check_file_exist(base_name)) {
            std::cout << "data base '" << base_name << "' is not exist" << std::endl;
            return;
        }

        if (command.empty()) {
            std::cout << "*missing arguments for function" << std::endl;
        }
        else if((command.size() >= 2) && (command[0] == 'I') && (command[1] == 'D')) {
            for (int l = 0; l < command.size(); ++l) {
                if (command[l] == ':') {
                    command.erase(command.begin(), command.begin() + l + 1);
                    break;
                }
            }

            _erase_space_begin(command);
            _erase_space_end(command);

            int id = 0;

            try {
                id = std::stoi(command);
                if (id <= 0) {
                    std::cout << "*invalid ID" << std::endl;
                    return;
                }
                --id;
            }
            catch(const std::exception& exc) {
                std::cout << "*invalid ID" << std::endl;
                return;
            }


            std::ifstream _r_file;
            _r_file.open(path + base_name + ".txt"); //read properties

            int property_count = 0;

            for (; !_r_file.eof(); ++property_count) {
                std::string line;
                std::getline(_r_file, line); 
            }

            _r_file.close(); //end read properties     

            
            std::ifstream _r_file1;
            _r_file1.open(path + base_name + "_table.txt"); //read data

            std::vector<std::string> data;

            while (!_r_file1.eof()) {
                std::string line;
                std::getline(_r_file1, line);

                if (line.empty()) { continue; }

                data.push_back(line);
            }

            _r_file1.close(); //end read data   


            if (data.size() <= (id * (property_count + 1))) {
                std::cout << "*invalid ID" << std::endl;
                return;
            }

            //data.erase(data.begin() + (id * (property_count + 1)), data.begin() + (property_count + 1) + (id * (property_count + 1)));
            for (int i = 0; i < property_count; ++i) {
                std::string property = data[id * (property_count + 1) + i];

                std::string::iterator delim = property.begin();
                while (*delim != ':') {
                    ++delim;
                }
                property.erase(delim + 1, property.end());

                std::cout << property << " ";

                std::string property_value;
                std::cin >> property_value;

                data[id * (property_count + 1) + i] = property + property_value;
            }

            std::ofstream _w_file1;
            _w_file1.open(path + base_name + "_table.txt"); //overwrite data
            
            for (int i = 0; i < data.size(); ++i) {
                _w_file1 << data[i] << std::endl;
            }

            _w_file1.close(); //end overwrite data
        }
        else {
            std::cout << "*invalid command" << std::endl;
        }
    }

    void delete_(std::string command) {
        std::string base_name = _get_base_name(command);

        if (!_check_file_exist(base_name)) {
            std::cout << "data base '" << base_name << "' is not exist" << std::endl;
            return;
        }

        if (command.empty()) {
            std::cout << "*missing arguments for function" << std::endl;
        }
        else if (command == "*") {
            std::ofstream _w_file;
            _w_file.open(path + base_name + "_table.txt"); //remove content
            /**/
            _w_file.close(); //end remove 
        }
        else if((command.size() >= 2) && (command[0] == 'I') && (command[1] == 'D')) {
            for (int l = 0; l < command.size(); ++l) {
                if (command[l] == ':') {
                    command.erase(command.begin(), command.begin() + l + 1);
                    break;
                }
            }

            _erase_space_begin(command);
            _erase_space_end(command);

            int id = 0;

            try {
                id = std::stoi(command);
                if (id <= 0) {
                    std::cout << "*invalid ID" << std::endl;
                    return;
                }
                --id;
            }
            catch(const std::exception& exc) {
                std::cout << "*invalid ID" << std::endl;
                return;
            }


            std::ifstream _r_file;
            _r_file.open(path + base_name + ".txt"); //read properties

            int property_count = 0;

            for (; !_r_file.eof(); ++property_count) {
                std::string line;
                std::getline(_r_file, line); 
            }

            _r_file.close(); //end read properties     

            
            std::ifstream _r_file1;
            _r_file1.open(path + base_name + "_table.txt"); //read data

            std::vector<std::string> data;

            while (!_r_file1.eof()) {
                std::string line;
                std::getline(_r_file1, line);

                if (line.empty()) { continue; }

                data.push_back(line);
            }

            _r_file1.close(); //end read data   


            if (data.size() <= (id * (property_count + 1))) {
                std::cout << "*invalid ID" << std::endl;
                return;
            }

            data.erase(data.begin() + (id * (property_count + 1)), data.begin() + (property_count + 1) + (id * (property_count + 1)));


            std::ofstream _w_file1;
            _w_file1.open(path + base_name + "_table.txt"); //overwrite data
            
            for (int i = 0; i < data.size(); ++i) {
                _w_file1 << data[i] << std::endl;
            }

            _w_file1.close(); //end overwrite data
        }
        else {
            std::cout << "*invalid command" << std::endl;
        }
    }

    void drop(std::string command) {
        std::string base_name = _get_base_name(command);

        if (!_check_file_exist(base_name)) {
            std::cout << "data base '" << base_name << "' is not exist" << std::endl;
            return;
        }

        if (!command.empty()) {
            std::cout << "*too many arguments for function" << std::endl;
        }
        else {
            std::string base = path + base_name + ".txt";
            std::string base_table = path + base_name + "_table.txt";

            std::remove(base.c_str());
            std::remove(base_table.c_str());
        }        
    }

private:
    bool _check_file_exist(std::string file_name) {
        file_name.insert(file_name.begin(), path.begin(), path.end());
        file_name += ".txt";
        return !(stat(file_name.c_str(), &info));
    }

    std::string _get_base_name(std::string& command) {
        _erase_space_begin(command);
        _erase_space_end(command);

        std::string base_name;

        std::string::iterator b_name_separator = command.begin();
        for (; b_name_separator != command.end(); ++b_name_separator) {
            if ((*b_name_separator == ':') || (*b_name_separator == ' ')) {
                break;
            }
        }

        base_name.assign(command.begin(), b_name_separator);

        if (b_name_separator == command.end()) {
            command.erase(command.begin(), b_name_separator);
        }
        else {
            command.erase(command.begin(), b_name_separator + 1);
        }

        return base_name;
    }

    void _erase_space_begin(std::string& command) {
        while(*command.begin() == ' ') {
            command.erase(command.begin());
        }
    }

    void _erase_space_end(std::string& command) {
        while(*(command.end() - 1) == ' ') {
            command.erase(command.end() - 1);
        }
    }

private:
    const std::string path;
    struct stat info;
};
