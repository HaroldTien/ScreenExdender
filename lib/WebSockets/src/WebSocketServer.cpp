#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sstream>

#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <map>
#include <iomanip>

// Include the header files that declare sha1 and base64_encode.
#include "../include/SHA1.h"
#include "../include/Base64.h"
#include "../include/WebSocketServer.h"

#include <netdb.h>



namespace WebSocket{
        int createServerSocket(int port){

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            std::cerr << "Error: Failed to create socket. Errno: " << errno << std::endl;
            throw std::runtime_error("Failed to create socket");
        }

        // Set socket options - IMPORTANT for allowing connections
        int opt = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            std::cerr << "Error: setsockopt failed. Errno: " << errno << std::endl;
            close(sockfd);
            throw std::runtime_error("setsockopt failed");
        }

        sockaddr_in server_address;
        std::memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = htonl(INADDR_ANY);  // Explicitly bind to all interfaces
        server_address.sin_port = htons(port);

        if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
            std::cerr << "Error: Failed to bind socket. Errno: " << errno << std::endl;
            perror("Bind failed");
            close(sockfd);
            throw std::runtime_error("Failed to bind socket");
        }

        if (listen(sockfd, SOMAXCONN) < 0) {
            std::cerr << "Error: Failed to listen on socket. Errno: " << errno << std::endl;
            close(sockfd);
            throw std::runtime_error("Failed to listen on socket");
        }

        // Print all available IP addresses for connection
        auto serverIPs = getServerIPs();
        std::cout << "\n=== Server Connection Information ===" << std::endl;
        std::cout << "Server is listening on port: " << port << std::endl;
        std::cout << "You can connect using any of these addresses:" << std::endl;
        for(const auto& ip : serverIPs) {
            std::cout << "  " << ip << ":" << port << std::endl;
        }
        std::cout << "==================================\n" << std::endl;

        return sockfd;
    }

    std::string read_http_request(int client_socket){
        std::cout << "Reading HTTP request..." << std::endl;
        const size_t BUFFER_SIZE = 4096;
        char buffer[BUFFER_SIZE];
        std::string request;


        ssize_t bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
        if(bytes_read <= 0){
            std::cerr << "Error: Failed to read from client. Errno: " << errno << std::endl;
            throw std::runtime_error("Failed to read from client");
        }

        buffer[bytes_read] = '\0';
        request = std::string(buffer);
        return request;
        
    }

    std::map<std::string, std::string> parse_http_header(const std::string& request){
        std::cout << "Parsing HTTP header..." << std::endl;
        std::map<std::string, std::string> headers; 
        std::istringstream header_stream(request);
        std::string header_line;

        std::getline(header_stream, header_line);
        while(std::getline(header_stream, header_line) && header_line != "\r"){
            if(!header_line.empty() && header_line.back() == '\r'){
                header_line.pop_back();
            }
            auto pos = header_line.find(": ");
            if(pos != std::string::npos){   
                headers[header_line.substr(0, pos)] = header_line.substr(pos + 2);
            }
        }
        return headers;
    }   

    std::string compute_accept_key(const std::string &key){
        std::cout << "Computing accept key..." << std::endl;
        std::string guid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
        std::string combined = key + guid;
        std::vector<uint8_t> hash = sha1(combined);
        std::string base64_hash = base64_encode(hash);
        return base64_hash;
    }

    void send_handshake_response(int client_socket, const std::string &accept_key){
        std::cout << "Sending handshake response..." << std::endl;
        std::string response = "HTTP/1.1 101 Switching Protocols\r\n";
        response += "Upgrade: websocket\r\n";
        response += "Connection: Upgrade\r\n";
        response += "Sec-WebSocket-Accept: " + accept_key + "\r\n";
        response += "\r\n";
        write(client_socket, response.c_str(), response.size());
    }

    std::vector<std::string> getServerIPs() {
        std::cout << "Getting server IPs..." << std::endl;
        std::vector<std::string> ipAddresses;
        
        char host_name[256];
        if (gethostname(host_name, sizeof(host_name)) != 0) {
            std::cerr << "Error getting hostname. Errno: " << errno << std::endl;
            return ipAddresses;
        }

        struct hostent *host_entry = gethostbyname(host_name);
        if (host_entry == nullptr) {
            std::cerr << "Error getting host entry. h_errno: " << h_errno << std::endl;
            return ipAddresses;
        }

        std::cout << "\n=== Server Network Information ===" << std::endl;
        std::cout << "Hostname: " << host_name << std::endl;
        std::cout << "Available IP addresses:" << std::endl;
        
        for (int i = 0; host_entry->h_addr_list[i] != nullptr; i++) {
            char ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, (struct in_addr *)host_entry->h_addr_list[i], ip, INET_ADDRSTRLEN);
            std::string ipStr(ip);
            ipAddresses.push_back(ipStr);
            std::cout << "IP " << i + 1 << ": " << ip << std::endl;
        }
        
        std::cout << "================================\n" << std::endl;
        
        return ipAddresses;
    }
}

