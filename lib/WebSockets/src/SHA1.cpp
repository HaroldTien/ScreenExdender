#include "../include/SHA1.h"

namespace WebSocket {

inline uint32_t rotate_left(uint32_t value, unsigned int bits) {
    return (value << bits) | (value >> (32 - bits));
}

std::vector<uint8_t> sha1(const std::string &data) {
    // Initialize the hash constants.
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    // Convert input string into a vector of bytes.
    std::vector<uint8_t> bytes(data.begin(), data.end());
    uint64_t original_bit_len = bytes.size() * 8;  // Calculate the length of the input in bits.
    
    bytes.push_back(0x80);                         // Append a single '1' bit (0x80) to the message.
    
    // Append '0' bytes until the total length is 448 modulo 512 bits.
    while ((bytes.size() * 8) % 512 != 448) {
        bytes.push_back(0);
    }
    
    // Append the original message length as a 64-bit big-endian integer.
    for (int i = 7; i >= 0; --i) {
        bytes.push_back((original_bit_len >> (i * 8)) & 0xFF);
    }
    
    // Process the message in 512-bit (64-byte) chunks.
    const size_t chunkCount = bytes.size() * 8 / 512;
    for (size_t chunk = 0; chunk < chunkCount; ++chunk) {
        uint32_t w[80];                          // Array to hold 80 words.
        size_t offset = chunk * 64;                // Calculate the starting index for this chunk.
        
        // Fill the first 16 words with the chunk data (in big-endian order).
        for (int i = 0; i < 16; ++i) {
            w[i] = (bytes[offset + i * 4] << 24) |
                   (bytes[offset + i * 4 + 1] << 16) |
                   (bytes[offset + i * 4 + 2] << 8) |
                   (bytes[offset + i * 4 + 3]);
        }
        // Extend the first 16 words into 80 words.
        for (int i = 16; i < 80; ++i) {
            w[i] = rotate_left(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }
        
        // Initialize working variables with the current hash value.
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;
        
        // Main loop: Process all 80 words.
        for (int i = 0; i < 80; ++i) {
            uint32_t f, k; // Variables for the current round's function and constant.
            if (i < 20) {                  // For rounds 0-19:
                f = (b & c) | ((~b) & d);  // f = (b AND c) OR ((NOT b) AND d)
                k = 0x5A827999;            // Constant for rounds 0-19.
            } else if (i < 40) {           // For rounds 20-39:
                f = b ^ c ^ d;           // f = b XOR c XOR d
                k = 0x6ED9EBA1;            // Constant for rounds 20-39.
            } else if (i < 60) {           // For rounds 40-59:
                f = (b & c) | (b & d) | (c & d); // f = (b AND c) OR (b AND d) OR (c AND d)
                k = 0x8F1BBCDC;            // Constant for rounds 40-59.
            } else {                       // For rounds 60-79:
                f = b ^ c ^ d;           // f = b XOR c XOR d
                k = 0xCA62C1D6;            // Constant for rounds 60-79.
            }
            uint32_t temp = rotate_left(a, 5) + f + e + k + w[i]; // Compute the temporary variable.
            e = d;                           // Shift the variables for the next round.
            d = c;
            c = rotate_left(b, 30);                  // Rotate b by 30 bits.
            b = a;
            a = temp;                        // Set a to the computed temporary value.
        }
        
        // Add the computed values back into the current hash state.
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }
    
    // Prepare a vector to hold the final 20-byte digest.
    std::vector<uint8_t> digest(20);
    // Lambda function to write a 32-bit integer into the digest in big-endian order.
    auto write_be = [&](uint32_t value, int offset) {
        digest[offset]   = (value >> 24) & 0xFF; // Most significant byte.
        digest[offset+1] = (value >> 16) & 0xFF;
        digest[offset+2] = (value >> 8) & 0xFF;
        digest[offset+3] = value & 0xFF;         // Least significant byte.
    };
    write_be(h0, 0);   // Write the first 32-bit block.
    write_be(h1, 4);   // Write the second 32-bit block.
    write_be(h2, 8);   // Write the third 32-bit block.
    write_be(h3, 12);  // Write the fourth 32-bit block.
    write_be(h4, 16);  // Write the fifth 32-bit block.
    
    return digest;     // Return the complete SHA-1 hash (20 bytes).
}

} // namespace WebSocket

