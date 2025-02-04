

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024




class CommunicationServer{
    public:
    CommunicationServer(int port);
    ~CommunicationServer();
    void start();
    void stop();
    void wallPaperSending(std::string wallPaperPath);
    void EstablishConnection();
    private:
    int sockfd, client_sockfd;
    int port;
    struct sockaddr_in server_addr,client_addr;
    bool isRunning;
};



