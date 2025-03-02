#ifndef BASE64_H
#define BASE64_H

#include <vector>
#include <cstdint>
#include <string>

// Declaration of the base64_encode function.
namespace WebSocket{
    std::string base64_encode(const std::vector<uint8_t> &data);
}


#endif // BASE64_H