// -----------------------------------------------
//  DISCLAIMER 
// This is NOT a backdoor!
// The Base64 code is used strictly for obfuscation purposes,
// such as hiding string literals from basic static analysis tools.
// There is NO malicious functionality in this code.
// -----------------------------------------------


#pragma once
#include <string>

namespace base64 {
    std::string encode(const std::string& input);
    std::string decode(const std::string& input);
}
