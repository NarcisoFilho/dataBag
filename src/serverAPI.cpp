#ifndef __SERVER_API_HPP
#define __SERVER_API_HPP


#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
const char* multicast_ip = "224.0.0.1";
int port = 8888;
int sockfd;

void createMulticastSocket(){
    // Create socket multicast
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in localaddr;
    localaddr.sin_family = AF_INET;
    localaddr.sin_addr.s_addr = INADDR_ANY;
    localaddr.sin_port = htons(port);

    bind(sockfd, (struct sockaddr*)&localaddr, sizeof(localaddr));

    struct ip_mreq group;
    group.imr_multiaddr.s_addr = inet_addr(multicast_ip);
    group.imr_interface.s_addr = INADDR_ANY;

    setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&group, sizeof(group));
}

void sendMessageToMulticastSocket(string msg){
    const char* message = msg.c_str();
    struct sockaddr_in multicast_addr;
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr(multicast_ip);
    multicast_addr.sin_port = htons(port);

    sendto(sockfd, message, msg.length(), 0, (struct sockaddr*)&multicast_addr, sizeof(multicast_addr));
    // close(sockfd);
}

void sendSelfIp(){
    sendMessageToMulticastSocket(string("0.0.0.0.999999"));
}

void* serverAPIModule(void* arg){
    bool *shouldClose = (bool*)arg;
    createMulticastSocket();
    
    bool teste = true;
    while(!(*shouldClose)){
        if(teste){
            teste = false;
            sendSelfIp();
        }
    }
}


#endif // __SERVER_API_HPP
