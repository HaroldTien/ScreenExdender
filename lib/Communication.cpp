#include "../include/Communication.h"
#include "../include/capturing.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>



#define HEIF_FILE_BUFFER_SIZE 4096


CommunicationServer::CommunicationServer(int port) : port(port), isRunning(false){
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Failed to create socket. Errno: " << errno << std::endl;
        throw std::runtime_error("Failed to create socket");
    }

    // Set socket options to allow address reuse
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Error: Failed to set socket options. Errno: " << errno << std::endl;
        close(sockfd);
        throw std::runtime_error("Failed to set socket options");
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind socket
    if (::bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error: Failed to bind socket. Errno: " << errno << std::endl;
        close(sockfd);
        throw std::runtime_error("Failed to bind socket");
    }

    // Listen for connections
    if (listen(sockfd, 1) < 0) {
        std::cerr << "Error: Failed to listen on socket. Errno: " << errno << std::endl;
        close(sockfd);
        throw std::runtime_error("Failed to listen on socket");
    }
    isRunning = true;
    std::cout << "Server is running on port " << port << std::endl;

}

void CommunicationServer::EstablishConnection(){

    socklen_t client_addr_len = sizeof(client_addr);
    client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_sockfd < 0) {
        std::cerr << "Error: Failed to accept connection. Errno: " << errno << std::endl;
        throw std::runtime_error("Failed to accept connection");
    }
    std::cout << "Connection accepted from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << std::endl;
    
}

void CommunicationServer::start(){
    isRunning = true;
}

void CommunicationServer::stop(){
    close(sockfd);
    isRunning = false;
}

CommunicationServer::~CommunicationServer(){
    stop();
}




