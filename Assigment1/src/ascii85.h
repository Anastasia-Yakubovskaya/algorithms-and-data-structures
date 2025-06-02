#ifndef ASCII85_H
#define ASCII85_H

#include <vector>
#include <string>
#include <utility>

class ASCII85 {
public:

    enum class Error {
        OK,                 
        EMPTY_INPUT,        
        BAD_Z_USAGE,        
        MULTIPLE_Z,         
        INVALID_CHAR,      
        INCOMPLETE_GROUP    
    };

    static std::pair<std::vector<unsigned char>, Error> decode(const std::string& s);
    
    static std::string encode(const std::vector<unsigned char>& v);
};

#endif
