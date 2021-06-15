#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <stdio.h>

class external_sort {
public:
    external_sort(std::string file_name) : size(0)
    {
        read_source.open(file_name);

        if (!read_source.is_open()) {
            std::cout << " -Unable to open file- " << std::endl;
            std::cout << " -No such file- " << std::endl;
            exit(0);
        }

        std::ifstream f_size(file_name);

        while (!f_size.eof()) {
            int tmp;
            f_size >> tmp;
            ++size;
        }

        f_size.close();
    }

    ~external_sort() {
        read_source.close();
    }

    void sort_file() {
        const int stream_count = 10;
        
        std::ofstream write[stream_count];

        open_files(write, stream_count);

        for (int write_count = 0; write_count < stream_count; ++write_count) {
            for (int i = 0; i < size / stream_count; ++i) {
                int tmp;
                read_source >> tmp;
                input_part.insert(tmp);
            }

            for (auto i = input_part.begin(); i != input_part.end(); ++i) {
                write[write_count] << *i << std::endl;
            }

            input_part.clear();
        }

        close_files(write, stream_count);

        //merge files
        std::ifstream read[stream_count];
        open_files(read, stream_count);
        output.open("output.txt");

        int final_sort[stream_count] = {0};
 
        for (int i = 0; i < size; ++i) {
            int min = __INT_MAX__;
            int min_num_file = 0;

            for (int write_count = 0; write_count < stream_count; ++write_count) {
                int tmp;
                read[write_count] >> tmp;
                final_sort[write_count] = tmp;
                
                if (tmp < min) {
                    min = tmp;
                    min_num_file = write_count;
                }
            }
            
            for (int write_count = 0; write_count < stream_count; ++write_count) {
                
                if (min_num_file == write_count) {
                    continue;
                }

                int count = 0;

                while (final_sort[write_count]) {
                    ++count;
                    final_sort[write_count] /= 10;
                }

                read[write_count].seekg(-count, std::ios::cur);
            }

            output << min << std::endl;
        }

        close_files(read, stream_count);

        for (int i = 0; i < stream_count; ++i) {
            std::remove((std::to_string(i) + ".txt").c_str());
        }
    }

private:
    template <typename FSTREAM>
    void open_files(FSTREAM file, int count) {
        for (int i = 0; i < count; ++i) {
            file[i].open(std::to_string(i) + ".txt");
        }
    }

    template <typename FSTREAM>
    void close_files(FSTREAM file, int count) {
        for (int i = 0; i < count; ++i) {
            file[i].close();
        }
    }


private:
    int size;
    std::ifstream read_source;
    std::ofstream output;
    std::multiset<int> input_part;
};

int main(int argc, char *argv[]) {
    if (argv[1] == nullptr) {
        std::cout << " -Unable to open file- " << std::endl;
        std::cout << " -File name missing- " << std::endl;
        exit(0);
    }
    else {
        external_sort m_sort(argv[1]);
        m_sort.sort_file();
    }
    
    return 0;
}