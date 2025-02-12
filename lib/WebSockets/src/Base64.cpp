
#include <string>
#include <vector>
#include <cstdint>


std::string base64_encode(const std::vector<uint8_t> &data) {
    // Base64 character set.
    static const char base64_chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    
    std::string encoded;   // String to hold the encoded output.
    size_t i = 0;          // Index for iterating through the data.
    uint32_t octet_a, octet_b, octet_c, triple; // Variables for 3-byte groups.
    
    // Process the input data in blocks of 3 bytes.
    while (i < data.size()) {
        // Get three bytes (or 0 if there is no data left).
        octet_a = i < data.size() ? data[i++] : 0;
        octet_b = i < data.size() ? data[i++] : 0;
        octet_c = i < data.size() ? data[i++] : 0;
        
        // Combine the three bytes into a 24-bit number.
        triple = (octet_a << 16) + (octet_b << 8) + octet_c;
        
        // Extract four 6-bit groups from the 24-bit number and map them to Base64 characters.
        encoded.push_back(base64_chars[(triple >> 18) & 0x3F]);
        encoded.push_back(base64_chars[(triple >> 12) & 0x3F]);
        // Use '=' as padding if the corresponding byte was missing.
        encoded.push_back(i - 1 < data.size() ? base64_chars[(triple >> 6) & 0x3F] : '=');
        encoded.push_back(i < data.size() ? base64_chars[triple & 0x3F] : '=');
    }
    
    return encoded;      // Return the Base64 encoded string.
}