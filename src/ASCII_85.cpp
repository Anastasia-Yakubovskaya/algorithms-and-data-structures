#include "ASCII_85.h"
#include <sstream>
#include <iomanip>
#include <cmath>    // Для функции pow
#include <cstring>  // Для функции strchr

std::string ASCII85::encode(const std::vector<unsigned char>& input) {
    std::ostringstream oss;
    size_t length = input.size();
    size_t i = 0;

    while (i < length) {
        unsigned long value = 0;
        int bytesToProcess = 0;

        // Берем 4 байта
        for (int j = 0; j < 4 && i < length; ++j) {
            value = (value << 8) | input[i++];
            bytesToProcess++;
        }

        // Если все 4 байта нулевые, добавляем 'z'
        if (value == 0 && bytesToProcess == 4) {
            oss << 'z';
            continue;
        }

        // Если байтов меньше 4, дополняем нулями
        if (bytesToProcess < 4) {
            value <<= 8 * (4 - bytesToProcess);
        }

        // Кодируем 4 байта в 5 символов ASCII85
        for (int j = 4; j >= 0; --j) {
            oss << static_cast<char>((value / static_cast<unsigned long>(std::pow(85, j))) % 85 + 33);
            value %= static_cast<unsigned long>(std::pow(85, j));
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
        int bytesProcessed = 0;

        // Обрабатываем 5 символов ASCII85
        for (int j = 0; j < 5 && i < length; ++j) {
            char ch = input[i++];
            if (ch == 'z') {
                value = 0;  // Если символ 'z', то считаем, что это 4 байта нулей.
                bytesProcessed = 4;
                break;
            } else if (ch < 33 || ch > 117) {
                throw std::invalid_argument("Invalid ASCII85 character");
            }
            value = value * 85 + (ch - 33);
            bytesProcessed++;
        }

        // Если мы обработали данные правильно
        if (bytesProcessed > 0) {
            for (int j = 3; j >= 0; --j) {
                if (j < bytesProcessed - 1) {  // Исправлено: добавляем только нужные байты
                    output.push_back(static_cast<unsigned char>((value >> (8 * j)) & 0xFF));
                }
            }
        } else {
            throw std::invalid_argument("Invalid ASCII85 encoding");
        }
    }

    return output;
}
