#include <iostream>
#include <vector>
#include <string>
#include "ascii85.h"

int main(int argc, char* argv[]) {
    try {
        if (argc == 1 || (argc == 2 && std::string(argv[1]) == "-e")) {
            std::string input;
            std::getline(std::cin, input);
            std::vector<uint8_t> inputData(input.begin(), input.end());
            std::cout << ASCII85::encode(inputData);
            return 0;
        } 
        else if (argc == 2 && std::string(argv[1]) == "-d") {

            std::string input;
            std::getline(std::cin, input);
            std::vector<uint8_t> decoded = ASCII85::decode(input);
            
  
            if (decoded.empty() && !input.empty()) {
                std::cerr << "Error: Invalid ASCII85 input data\n";
                return 1;  
            }
            
            std::string result(decoded.begin(), decoded.end());
            std::cout << result;
            return 0;
        }
        else {
            std::cerr << "Usage: " << argv[0] << " [-e|-d]\n";
            return 2;  
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 3;  
    }
}
