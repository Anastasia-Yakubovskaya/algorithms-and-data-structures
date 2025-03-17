#ifndef ASCII85_H
#define ASCII85_H

#include <vector>
#include <string>
#include <stdexcept>

class ASCII85 {
public:
    // Кодирование данных в ASCII85
    static std::string encode(const std::vector<unsigned char>& input);

    // Декодирование ASCII85 в бинарные данные
    static std::vector<unsigned char> decode(const std::string& input);
};

#endif // ASCII85_H
