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
#include "SHA1.h"
#include "Base64.h"

int createServerSocket(int port){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Failed to create socket. Errno: " << errno << std::endl;
        throw std::runtime_error("Failed to create socket");
    }

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in server_address;
    std::memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error: Failed to bind socket. Errno: " << errno << std::endl;
        throw std::runtime_error("Failed to bind socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0) {
        std::cerr << "Error: Failed to listen on socket. Errno: " << errno << std::endl;
        throw std::runtime_error("Failed to listen on socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port << std::endl;

    return sockfd;
}

std::string read_http_request(int client_socket){

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

std::map<std::string, std::string> parse_http_hearder(const std::string& request){
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
    std::string guid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::string combined = key + guid;
    std::vector<uint8_t> hash = sha1(combined);
    std::string base64_hash = base64_encode(hash);
    return base64_hash;
}

void send_handshake_response(int client_socket, const std::string &accept_key){
    std::string response = "HTTP/1.1 101 Switching Protocols\r\n";
    response += "Upgrade: websocket\r\n";
    response += "Connection: Upgrade\r\n";
    response += "Sec-WebSocket-Accept: " + accept_key + "\r\n";
    response += "\r\n";
    write(client_socket, response.c_str(), response.size());
}



