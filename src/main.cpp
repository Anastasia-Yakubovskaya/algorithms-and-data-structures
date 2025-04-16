#include <iostream>
#include <vector>
#include <string>
#include "ASCII_85.h"

int main(int argc, char* argv[]) {

    if (argc == 1) {
        std::string input;
        std::getline(std::cin, input);
        std::vector<unsigned char> inputData(input.begin(), input.end());
        std::cout << ASCII85::encode(inputData);
        return 0;
    }
    
 
    if (argc == 2) {
        std::string option = argv[1];
        
        if (option == "-e") {

            std::string input;
            std::getline(std::cin, input);
            std::vector<unsigned char> inputData(input.begin(), input.end());
            std::cout << ASCII85::encode(inputData)<< "\n";
            return 0;
        } 
        else if (option == "-d") {

            std::string input;
            std::getline(std::cin, input);
            try {
                std::vector<unsigned char> decoded = ASCII85::decode(input);
                std::string result(decoded.begin(), decoded.end());
                std::cout << result << "\n";
                return 0;
            } catch (const std::exception& e) {
                std::cerr << e.what();
                return 1;
            }
        }
    }


    return 1;
}
