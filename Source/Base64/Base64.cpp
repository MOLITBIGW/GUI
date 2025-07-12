// -----------------------------------------------
//  DISCLAIMER 
// This is NOT a backdoor!
// The Base64 code is used strictly for obfuscation purposes,
// such as hiding string literals from basic static analysis tools.
// There is NO malicious functionality in this code.
// -----------------------------------------------


#include "Base64.hh"
#include <vector>

namespace base64 {
    static const char base64_chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static inline bool is_base64(unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }

    std::string encode(const std::string& input) {
        std::string ret;
        int val = 0, valb = -6;
        for (unsigned char c : input) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                ret.push_back(base64_chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6) ret.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (ret.size() % 4) ret.push_back('=');
        return ret;
    }

    std::string decode(const std::string& input) {
        std::vector<int> T(256, -1);
        for (int i = 0; i < 64; i++) T[base64_chars[i]] = i;

        std::string output;
        int val = 0, valb = -8;
        for (unsigned char c : input) {
            if (T[c] == -1) break;
            val = (val << 6) + T[c];
            valb += 6;
            if (valb >= 0) {
                output.push_back(char((val >> valb) & 0xFF));
                valb -= 8;
            }
        }
        return output;
    }
}
