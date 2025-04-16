#ifndef ASCII_85_H
#define ASCII_85_H

#include <vector>
#include <string>
#include <stdexcept>

class ASCII85 {
public:

    static const char ASCII85_CHARS[];

  
    static std::string encode(const std::vector<unsigned char>& input);


    static std::vector<unsigned char> decode(const std::string& input);
};

#endif // ASCII_85_H
