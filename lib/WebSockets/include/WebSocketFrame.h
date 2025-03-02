#ifndef WEBSOCKET_FRAME_H
#define WEBSOCKET_FRAME_H

#include <cstdint>
#include <vector>

// WebSocket Frame Handler
// 處理 WebSocket 幀的類別

// Constants for WebSocket opcodes
// WebSocket 操作碼常量
namespace WebSocketOpcode {
    const uint8_t CONTINUATION = 0x0;  // 續傳幀
    const uint8_t TEXT = 0x1;          // 文本幀
    const uint8_t BINARY = 0x2;        // 二進制幀
    const uint8_t CLOSE = 0x8;         // 關閉幀
    const uint8_t PING = 0x9;          // Ping 幀
    const uint8_t PONG = 0xA;          // Pong 幀
}

// Main function to handle incoming WebSocket frames
// 處理傳入的 WebSocket 幀的主要函數

namespace WebSocket {
    void handle_websocket_frame(int client_socket);
}


// Helper functions could be added here if needed
// 如果需要的話，可以在這裡添加輔助函數

#endif // WEBSOCKET_FRAME_H

