#include "ASCII_85.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cctype>

const char ASCII85::ASCII85_CHARS[85] = {
    '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*',
    '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    ':', ';', '<', '=', '>', '?', '@',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    '[', '\\', ']', '^', '_', '`',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u'
};

std::string ASCII85::encode(const std::vector<unsigned char>& input) {
    std::ostringstream oss;
    size_t i = 0;
    const size_t len = input.size();

    while (i < len) {
        uint32_t value = 0;
        int count = 0;

        while (count < 4 && i < len) {
            value = (value << 8) | input[i++];
            count++;
        }

        if (count == 4 && value == 0) {
            oss << 'z';
            continue;
        }

        if (count < 4) {
            value <<= 8 * (4 - count);
        }

        char encoded[5];
        for (int j = 4; j >= 0; --j) {
            encoded[j] = ASCII85_CHARS[value % 85];
            value /= 85;
        }
        
        for (int j = 0; j < count + 1; ++j) {
            oss << encoded[j];
        }
    }

    return oss.str();
}

std::vector<unsigned char> ASCII85::decode(const std::string& input) {
    std::vector<unsigned char> output;
    size_t i = 0;
    const size_t len = input.size();

    while (i < len) {
        while (i < len && (isspace(input[i]) || static_cast<unsigned char>(input[i]) < 33)) {
            i++;
        }
        if (i >= len) break;

        if (input[i] == 'z') {
            output.insert(output.end(), 4, 0);
            i++;
            continue;
        }

        uint32_t value = 0;
        int count = 0;
        bool error = false;

        while (count < 5 && i < len && !error) {
            while (i < len && (isspace(input[i]) || static_cast<unsigned char>(input[i]) < 33)) {
                i++;
            }
            if (i >= len) break;

            char c = input[i++];
            
            if (c < '!' || c > 'u') {
                error = true;
                break;
            }

            value = value * 85 + (c - '!');
            count++;
        }

        if (error) {
            return std::vector<unsigned char>();
        }

        if (count < 5) {
            for (int j = count; j < 5; ++j) {
                value = value * 85 + 84; 
            }
        }

        int bytes_to_write = (count == 5) ? 4 : std::max(0, count - 1);
        for (int j = 0; j < bytes_to_write; ++j) {
            output.push_back((value >> (24 - j * 8)) & 0xFF);
        }
    }

    return output;
}
