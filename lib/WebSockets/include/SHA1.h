#ifndef SHA1_H
#define SHA1_H

#include <vector>
#include <cstdint>
#include <string>


namespace WebSocket{
    std::vector<uint8_t> sha1(const std::string &data);
}
// Declaration of the sha1 function.


#endif // SHA1_H