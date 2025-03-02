#include <cstdlib>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include "../include/WebSocketServer.h"
#include "../include/WebSocketFrame.h"


int main() {
    const int port = 8080;
    int server_sock = WebSocket::createServerSocket(port);

    while (true) {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        std::cout << "Waiting for client connection..." << std::endl;
        int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("accept failed");
            continue;
        }
        std::cout << "Client connected.\n";
        
        // 1. Read HTTP handshake request:
        std::string request = WebSocket::read_http_request(client_sock);
        if (request.empty()) {
            close(client_sock);
            continue;
        }
        
        // 2. Parse headers:
        auto headers = WebSocket::parse_http_header(request);
        if (headers.find("Sec-WebSocket-Key") == headers.end()) {
            std::cerr << "No Sec-WebSocket-Key header found.\n";
            close(client_sock);
            continue;
        }
        std::string client_key = headers["Sec-WebSocket-Key"];
        
        // 3. Compute accept key:
        std::string accept_key = WebSocket::compute_accept_key(client_key);
        
        // 4. Send handshake response:
        WebSocket::send_handshake_response(client_sock, accept_key);
        std::cout << "Handshake completed.\n";
        
        // 5. Enter frame processing loop:
        WebSocket::handle_websocket_frame(client_sock);
        
        close(client_sock);
        std::cout << "Client disconnected.\n";
    }
    
    close(server_sock);
    return 0;
}
