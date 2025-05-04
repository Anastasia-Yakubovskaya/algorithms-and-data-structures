#ifndef ASCII85_H
#define ASCII85_H

#include <vector>
#include <string>

class ASCII85 {
public:
    static std::string encode(const std::vector<uint8_t>& input);
    static std::vector<uint8_t> decode(const std::string& input); 
};

#endif
