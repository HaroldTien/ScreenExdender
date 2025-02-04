#include "../include/ConnectionCodeGeneration.h"
#include <iostream>
#include <string>
#include <random>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;



std::string getIPAddress() {
    struct ifaddrs *interfaces = nullptr;
    struct ifaddrs *temp_addr = nullptr;
    std::string ipAddress = "";

    // Retrieve the current interfaces
    if (getifaddrs(&interfaces) == 0) {
        temp_addr = interfaces;

        while (temp_addr != nullptr) {
            // Check if the address is IPv4
            if (temp_addr->ifa_addr && temp_addr->ifa_addr->sa_family == AF_INET) {
                // Get the interface name
                std::string interfaceName = temp_addr->ifa_name;

                // Skip the loopback interface
                if (interfaceName != "lo0") {
                    // Get the IP address
                    char addressBuffer[INET_ADDRSTRLEN];
                    void* addrPtr = &((struct sockaddr_in*)temp_addr->ifa_addr)->sin_addr;

                    inet_ntop(AF_INET, addrPtr, addressBuffer, INET_ADDRSTRLEN);
                    ipAddress = std::string(addressBuffer);
                    break;
                }
            }
            temp_addr = temp_addr->ifa_next;
        }
    }

    // Free memory allocated for the linked list
    freeifaddrs(interfaces);
    return ipAddress;
}


string ConnectionCodeGeneration(int PORT) {
    return getIPAddress()+"#"+to_string(PORT);
}

