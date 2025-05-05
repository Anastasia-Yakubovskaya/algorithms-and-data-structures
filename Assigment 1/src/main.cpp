#include "ascii85.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    bool decode_mode = false;
    
    if (argc > 1 && std::string(argv[1]) == "-d") {
        decode_mode = true;
    }
    
    try {
        std::string input;
        std::getline(std::cin, input, '\0');
        
        if (decode_mode) {
            auto [result, error] = ASCII85::decode(input);
            if (error != ASCII85::Error::OK) {
                std::cerr << "Ошибка декодирования" << std::endl;
                return 1;
            }
            std::cout.write(reinterpret_cast<const char*>(result.data()), result.size());
        } else {
            std::vector<unsigned char> data(input.begin(), input.end());
            std::string encoded = ASCII85::encode(data);
            std::cout << encoded;
        }
        return 0;
    } catch (...) {
        return 1;
    }
}
