#include "ASCII_85.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstring>

// Инициализация массива символов ASCII85
const char ASCII85::ASCII85_CHARS[] = {
    '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*',
    '+', ',', '-', '.', '/', '0', '1', '2', '3', '4',
    '5', '6', '7', '8', '9', ':', ';', '<', '=', '>',
    '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\',
    ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '{', '|', '}', '~'
};

std::string ASCII85::encode(const std::vector<unsigned char>& input) {
    std::ostringstream oss;
    size_t length = input.size();
    size_t i = 0;

    while (i < length) {
        unsigned long value = 0;
        int bytesToProcess = 0;


        for (int j = 0; j < 4 && i < length; ++j) {
            value = (value << 8) | input[i++];
            bytesToProcess++;
        }


        if (value == 0 && bytesToProcess == 4) {
            oss << 'z';
            continue;
        }


        if (bytesToProcess < 4) {
            value <<= 8 * (4 - bytesToProcess);
        }


        char encodedBlock[5];
        for (int j = 4; j >= 0; --j) {
            encodedBlock[j] = ASCII85_CHARS[value % 85];
            value /= 85;
        }

 
        for (int j = 0; j < bytesToProcess + 1; ++j) {
            oss << encodedBlock[j];
        }
    }

    return oss.str();
}

std::vector<unsigned char> ASCII85::decode(const std::string& input) {
    std::vector<unsigned char> output;
    size_t length = input.size();
    size_t i = 0;

    while (i < length) {
        unsigned long value = 0;
        int count = 0;

 
        if (input[i] == 'z') {
            output.insert(output.end(), {0, 0, 0, 0});
            i++;
            continue;
        }

  
        for (int j = 0; j < 5 && i < length; ++j) {
            char ch = input[i++];
            if (ch < 33 || ch > 117) {
                throw std::invalid_argument("Invalid ASCII85 character");
            }
            value = value * 85 + (ch - 33);
            count++;
        }

   
        if (count < 5) {
            for (int j = count; j < 5; ++j) {
                value = value * 85 + 84;  // Символ 'u' (117) - 33 = 84
            }
        }


        unsigned char decodedBlock[4];
        for (int j = 0; j < 4; ++j) {
            decodedBlock[j] = static_cast<unsigned char>((value >> (8 * (3 - j))) & 0xFF);
        }

        output.insert(output.end(), decodedBlock, decodedBlock + (count - 1));
    }

    return output;
}
