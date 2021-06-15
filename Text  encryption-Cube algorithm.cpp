#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <time.h>

using std::string;
using std::vector;

void rotateCube(string& text, char directory) {
    std::swap(text[0], text[1]);
    std::swap(text[2], text[3]);
    std::swap(text[4], text[5]);
    std::swap(text[6], text[7]);

    if (directory == 'U') {
        std::swap(text[1], text[2]);
        std::swap(text[5], text[6]);
    }
    else if (directory == 'D') {
        std::swap(text[0], text[3]);
        std::swap(text[4], text[7]);
    }
    else if (directory == 'L') {
        std::swap(text[1], text[4]);
        std::swap(text[3], text[6]);
    }
    else if (directory == 'R') {
        std::swap(text[0], text[5]);
        std::swap(text[2], text[7]);
    }
}

class Cube {
public:
    Cube(const string& input) { buffer_ = input; }

    string getText() const { return buffer_; }
    string getEncrypt() const { return encrypt_; }

    void setEncrypt(const string& input) { encrypt_ = input; }
    void setText(const string& input) { buffer_ = input; }

private:
    string buffer_;
    string encrypt_;
};

class Encrypt {
public:
    Encrypt(string input) {
        int c_count = (input.size() / 8) + 1;

        for (int i = 0; i < c_count; ++i) {
            if (input.size() <= 8) {
                while (input.size() < 8) {
                    input.push_back('0');
                }

                cube_buffer_.push_back(new Cube(input));
                break;
            }

            cube_buffer_.push_back(new Cube(string(input.begin(), input.begin() + 8)));

            input.erase(input.begin(), input.begin() + 8);
        }

        randomEncrypt();
    }

    ~Encrypt() {
        std::for_each(cube_buffer_.begin(), cube_buffer_.end(), [](Cube* element) {
            delete element;
        });
    }

public:
    string getEncrypt() const { return encrypt_; }
    string getEncryptText() const { return text_buffer_; }

    int getCubeCount() const { return cube_buffer_.size(); }

    void randomEncrypt() {
        std::srand(time(NULL));

        encrypt_.clear();
        text_buffer_.clear();

        vector<int> rotate_count = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vector<char> rotate_direct = {'U', 'D', 'L', 'R'};

        //create encrypt algorithm
        //{
        for (int i = 0; i < cube_buffer_.size(); ++i) {
            std::random_shuffle(rotate_count.begin(), rotate_count.end());

            int count = rotate_count[0];

            string temp_encrypt;

            for (int j = 0; j < count; ++j) {
                std::random_shuffle(rotate_direct.begin(), rotate_direct.end());
                temp_encrypt += rotate_direct[0];
                temp_encrypt += ':';
            }
            temp_encrypt.pop_back();

            cube_buffer_[i]->setEncrypt(temp_encrypt);
            encrypt_ += std::to_string(i) + ':' + temp_encrypt + ',';
        }
        encrypt_.pop_back();
        //}

        //encrypting cubes
        for (int i = 0; i < cube_buffer_.size(); ++i) {
            string temp_text = cube_buffer_[i]->getText();
            string temp_encrypt = cube_buffer_[i]->getEncrypt();

            temp_encrypt.erase(
                        std::remove_if(temp_encrypt.begin(), temp_encrypt.end(), [](char ch) { return ch == ':'; })
                        , temp_encrypt.end()
                        );

            for (int j = 0; j < temp_encrypt.size(); ++j) {
                if (temp_encrypt[j] == 'U') {
                    rotateCube(temp_text, 'U');
                }
                else if (temp_encrypt[j] == 'D') {
                    rotateCube(temp_text, 'D');
                }
                else if (temp_encrypt[j] == 'L') {
                    rotateCube(temp_text, 'L');
                }
                else if (temp_encrypt[j] == 'R') {
                    rotateCube(temp_text, 'R');
                }
            }

            cube_buffer_[i]->setText(temp_text);
        }

        for (int i = 0; i < cube_buffer_.size(); ++i) {
            text_buffer_ += cube_buffer_[i]->getText();
        }
    }

private:
    string encrypt_;
    string text_buffer_;
    vector<Cube*> cube_buffer_;
};

class Decrypt {
public:
    Decrypt(const string& text, const string& decrypt)
        : encrypt_(decrypt), text_buffer_(text)
    {
        string temp_encrypt = encrypt_;
        temp_encrypt.erase(
                    std::remove_if(temp_encrypt.begin(), temp_encrypt.end(), [](char ch) { return ch == ':'; })
                    , temp_encrypt.end()
                    );

        //cubes encryptions
        std::vector<string> cubes_encrypt;
        string temp; //temporary string

        for (int i = 0; i < temp_encrypt.size(); ++i) {
            if (temp_encrypt[i] != ',') {
                temp.push_back(temp_encrypt[i]);
            }
            else {
                cubes_encrypt.push_back(temp);
                temp.clear();
            }
        }
        cubes_encrypt.push_back(temp);

        //remove cube index
        std::for_each(cubes_encrypt.begin(), cubes_encrypt.end(), [](string& element) {
                element.erase(element.begin());
            });

        //decryption
        string complete_decrypt_text;

        for (int i = 0; i < cubes_encrypt.size(); ++i) {
            //current cube encryption
            string curr_cube_encrypt = cubes_encrypt[i];

            //first 8 letters
            string temp_text_buffer = text_buffer_.substr(0, 8);
            text_buffer_.erase(0, 8);

            for (int j = curr_cube_encrypt.size(); j >= 0; --j) {
                if (curr_cube_encrypt[j] == 'U') {
                    rotateCube(temp_text_buffer, 'D');
                }
                else if (curr_cube_encrypt[j] == 'D') {
                    rotateCube(temp_text_buffer, 'U');
                }
                else if (curr_cube_encrypt[j] == 'L') {
                    rotateCube(temp_text_buffer, 'R');
                }
                else if (curr_cube_encrypt[j] == 'R') {
                    rotateCube(temp_text_buffer, 'L');
                }
            }

            complete_decrypt_text += temp_text_buffer;
        }

        for (int i = complete_decrypt_text.size() - 1; complete_decrypt_text[i] == '0'; --i) {
            complete_decrypt_text.erase(complete_decrypt_text.end() - 1);
        }

        text_buffer_ = complete_decrypt_text;
    }

    string getDecryptText() const {
        return text_buffer_;
    }

private:
    string encrypt_;
    string text_buffer_;
};

int main() {
    std::ifstream file("encrypt_text.txt");
    string file_text;

    if (!file.is_open()) {
        return 0;
    }

    while (!file.eof()) {
        string temp;
        std::getline(file, temp);

        file_text += temp;
    }

    Encrypt enc(file_text);
    Decrypt dec(enc.getEncryptText(), enc.getEncrypt());

    std::cout << "File text: " << file_text << std::endl;
    std::cout << "Encrypted text: " << enc.getEncryptText() << std::endl;
    std::cout << "Encryption: " << enc.getEncrypt() << std::endl;
    std::cout << "Decrypted text: " << dec.getDecryptText();

    return 0;
}
