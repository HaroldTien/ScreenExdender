#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <map>
#include "../include/WebSocketFrame.h"

using namespace WebSocketOpcode;

namespace WebSocket {

void handle_websocket_frame(int client_socket) {
    while(true){
            
    uint8_t header[2];
    ssize_t header_size = read(client_socket, header, 2);

    if(header_size != 2) {
        std::cerr << "Failed to read header" << std::endl;
        return;
    }

    if (header_size != 2) {
        std::cerr << "Failed to read header" << std::endl;
        return;
    }

    bool FIN = header[0] & 0x80;
    bool RSV1 = header[0] & 0x40;
    bool RSV2 = header[0] & 0x20;
    bool RSV3 = header[0] & 0x10;
    bool masked = header[1] & 0x80;
    uint8_t opcode = header[0] & 0x0F;

    uint64_t payload_length = header[1] & 0x7F;

    if(payload_length == 126) {
        uint8_t ext_length[2];
        ssize_t length_size = read(client_socket, ext_length, 2);
        if(length_size != 2) {
            std::cerr << "Failed to read length" << std::endl;
            return;
        }
        payload_length = (ext_length[0] << 8) | ext_length[1];
        
    } else if(payload_length == 127) {
        uint8_t ext_length[8];
        ssize_t length_size = read(client_socket, ext_length, 8);
        if(length_size != 8) {
            std::cerr << "Failed to read length" << std::endl;
            return;
        }
        payload_length = 0;
        for(int i = 0 ; i < 8 ; i++) {
            payload_length = (payload_length << 8) + ext_length[i];
        }
    }   
    uint8_t maskKey[4];
    if(masked) {
        
        ssize_t mask_size = read(client_socket, maskKey , 4);
        if(mask_size != 4) {
            std::cerr << "Failed to read mask" << std::endl;
            return;
        }        
    }

    std::vector<uint8_t> payload(payload_length);
    size_t received_data = 0;

    while( payload_length > received_data) {
        ssize_t bytes_read = read( client_socket, &payload[received_data] , payload_length - received_data);
        if(bytes_read < 0) {
            std::cerr << "Failed to read data" << std::endl;
            return;
        }
        received_data += bytes_read;
    }

    if(masked) {
        for(size_t i = 0 ; i < payload_length ; i++) {
            payload[i] = payload[i] ^ maskKey[i % 4];
        }   
    }

    switch(opcode) {
        case CONTINUATION: // Continuation frame
            // Handle continuation frame
            break;
            
        case TEXT: { // Text frame
            std::string text_data(payload.begin(), payload.end());
            std::cout << text_data << std::endl;
            break;
        }
            
        case BINARY: { // Binary frame
            // Handle binary data directly from payload vector
            break;
        }
            
        case CLOSE: { // Close frame
            // Send close frame back
            uint8_t close_frame[] = {0x88, 0x00}; // FIN=1, Opcode=8 (close)
            write(client_socket, close_frame, 2);
            return;
        }
            
        case PING: { // Ping frame
            // Send pong frame
            uint8_t pong_frame[] = {0x8A, 0x00}; // FIN=1, Opcode=10 (pong)
            write(client_socket, pong_frame, 2);
            break;
        }
            
        case PONG: // Pong frame
            // Can ignore pong framesd  
            break;
            
        default:
            std::cerr << "Unknown opcode: " << std::hex << (int)opcode << std::endl;
            break;
    }

    if(!FIN){
        std::cout << "Continuation frame" << std::endl;
        break;
    }

    }
}

bool send_websocket_textMassage(int client_socket, const std::string &data){
    std::vector<uint8_t> frame;
    uint8_t first_byte = 0x80 | TEXT;
    frame.push_back(first_byte);
    
    size_t payload_length = data.size();
    if(payload_length <= 125){
        frame.push_back(payload_length);
    }else if(payload_length <= 65535){
        frame.push_back(126);
        frame.push_back((payload_length >> 8) & 0xFF);
        frame.push_back(payload_length & 0xFF);
    }else{
        frame.push_back(127);
        frame.push_back((payload_length >> 56) & 0xFF);
        frame.push_back((payload_length >> 48) & 0xFF);
        frame.push_back((payload_length >> 40) & 0xFF);
        frame.push_back((payload_length >> 32) & 0xFF);
        frame.push_back((payload_length >> 24) & 0xFF);
        frame.push_back((payload_length >> 16) & 0xFF);
        frame.push_back((payload_length >> 8) & 0xFF);
        frame.push_back(payload_length & 0xFF);
    }

    frame.insert(frame.end(), data.begin(), data.end());

    write(client_socket, frame.data(), frame.size());
    return true;
    
}

} // namespace WebSocket



