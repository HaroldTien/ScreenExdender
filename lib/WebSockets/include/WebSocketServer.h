#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <netinet/in.h>

namespace WebSocket {

    std::vector<std::string> getServerIPs();

    /**
     * 建立一個綁定到指定 port 的 server socket。
     * @param port 要綁定的 port 號碼。
     * @return 回傳 socket 檔案描述符。
     * @throws std::runtime_error 當創建 socket 失敗時。
     */
    int createServerSocket(int port);

    /**
     * 從 client socket 讀取 HTTP request。
     * @param client_socket client socket 的檔案描述符。
     * @return 回傳 HTTP request 的字串。
     * @throws std::runtime_error 當讀取失敗時。
     */
    std::string read_http_request(int client_socket);

    /**
     * 從 HTTP request 字串解析 HTTP header。
     * @param request HTTP request 的字串。
     * @return 回傳一個 header 名稱到值的映射 (map)。
     */
    std::map<std::string, std::string> parse_http_header(const std::string& request);

    /**
     * 計算 WebSocket 握手時的 accept key。
     * @param key 客戶端提供的 Sec-WebSocket-Key。
     * @return 計算後的 accept key。
     */
    std::string compute_accept_key(const std::string &key);

    /**
     * 通過提供的 client socket 發送握手回應。
     * @param client_socket client socket 的檔案描述符。
     * @param accept_key 計算出的 Sec-WebSocket-Accept key。
     */
    void send_handshake_response(int client_socket, const std::string &accept_key);

    /**
     * 將一個 32 位元數值左旋指定的位數。
     * @param value 要旋轉的值。
     * @param bits 要旋轉的位數。
     * @return 旋轉後的值。
     */
    inline uint32_t rotate_left(uint32_t value, unsigned int bits) {
        return (value << bits) | (value >> (32 - bits));
    }

    /**
     * 針對輸入資料計算 SHA-1 雜湊值。
     * @param data 要進行雜湊運算的字串。
     * @return 回傳一個包含雜湊值的位元組向量（vector）。
     */
    std::vector<uint8_t> sha1(const std::string &data);

    /**
     * 將二進位資料進行 Base64 編碼。
     * @param data 要編碼的資料。
     * @return 回傳 Base64 編碼後的字串。
     */
    std::string base64_encode(const std::vector<uint8_t> &data);

    // 常量定義
    constexpr size_t BUFFER_SIZE = 4096;  // Socket 操作的預設緩衝區大小

    // Socket 操作錯誤訊息
    constexpr const char* ERR_SOCKET_CREATE = "Failed to create socket";
    constexpr const char* ERR_SOCKET_BIND = "Failed to bind socket";
    constexpr const char* ERR_SOCKET_LISTEN = "Failed to listen on socket";
    constexpr const char* ERR_SOCKET_READ   = "Failed to read from client";

} // namespace WebSocket

#endif // WEBSOCKET_SERVER_H
