#include "ascii85.h"
#include <vector>
#include <string>

std::vector<unsigned char> ASCII85::decode(const std::string& s) 
{
    std::vector<unsigned char> out;
    unsigned int num = 0;
    size_t n = 0;
    bool z = false;

    if (s.empty()) throw "empty";

    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        
        if (c == '~' && i+1 < s.size() && s[i+1] == '>') break;
        if (isspace(c)) continue;
        
        if (c == 'z') {
            if (n != 0) throw "bad z";
            if (z) throw "many z";
            out.insert(out.end(), 4, 0);
            z = true;
            continue;
        }
        
        if (c < '!' || c > 'u') throw "bad char";
        
        num = num * 85 + (c - '!');
        n++;
        
        if (n == 5) {
            out.push_back((num >> 24) & 0xFF);
            out.push_back((num >> 16) & 0xFF);
            out.push_back((num >> 8) & 0xFF);
            out.push_back(num & 0xFF);
            num = n = 0;
            z = false;
        }
    }
    
    if (n > 1) {
        for (size_t i = n; i < 5; i++) num = num * 85 + 84;
        for (size_t i = 0; i < n-1; i++) {
            out.push_back((num >> (24 - i*8)) & 0xFF);
        }
    }
    else if (n == 1) throw "incomplete";

    return out;
}

std::string ASCII85::encode(const std::vector<unsigned char>& v)
{
    std::string s;
    unsigned int num = 0;
    size_t n = 0;

    for (size_t i = 0; i < v.size(); i++) {
        num = (num << 8) | v[i];
        n++;
        
        if (n == 4) {
            if (num == 0) s += 'z';
            else {
                char a[5];
                for (int j = 4; j >= 0; j--) {
                    a[j] = (num % 85) + '!';
                    num /= 85;
                }
                s.append(a, 5);
            }
            num = n = 0;
        }
    }
    
    if (n > 0) {
        num <<= (4-n)*8;
        char a[5];
        for (int j = 4; j >= 0; j--) {
            a[j] = (num % 85) + '!';
            num /= 85;
        }
        s.append(a, n+1);
    }

    return s;
}
