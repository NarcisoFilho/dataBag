#ifndef __FRONT_END_HPP
#define __FRONT_END_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <fstream> 


#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <netdb.h> 
#include <arpa/inet.h>

#include "global_definitions.hpp"
#include "clientStateInformationStruct.hpp"

using namespace std;

struct hostent* dataBag_server_host_global;
struct in_addr ip_address_global;

void getCurrentRM(struct in_addr* ip_address, struct hostent* dataBag_server_host){
    // string rm_ip = ??? pegar por multicast;
    // string rm_ip = getIPRm();

    // ip_address->s_addr = inet_addr(rm_ip.c_str());
    // dataBag_server_host = gethostbyaddr(&ip_address, sizeof(ip_address), AF_INET);
    dataBag_server_host = gethostbyname("localhost");

    dataBag_server_host_global= dataBag_server_host;
    ip_address_global = *ip_address;
}

void getCurrentRM(){
    // string rm_ip = ??? pegar por multicast;
    // ip_address_global->s_addr = inet_addr(rm_ip.c_str());
    // dataBag_server_host_global = gethostbyaddr(&ip_address, sizeof(ip_address), AF_INET);
    dataBag_server_host_global = gethostbyname("localhost");
}

void reconectInfoSock(ClientStateInformation* clientStateInformation){
  struct sockaddr_in server_sentinel_socket_addr; 
  server_sentinel_socket_addr.sin_family = AF_INET;
  server_sentinel_socket_addr.sin_port = htons(SENTINEL_SOCKET_PORT);
  server_sentinel_socket_addr.sin_addr = *((struct in_addr*)dataBag_server_host_global->h_addr_list[0]);
  bzero(&(server_sentinel_socket_addr.sin_zero), 8);
  
  connect(clientStateInformation->info_communication_socket, (struct sockaddr *)&server_sentinel_socket_addr, sizeof(server_sentinel_socket_addr));

}

void reconectDataSock(ClientStateInformation* clientStateInformation){
      // TEMP socket to listen SYNC Data socket
  int temp_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in  temp_socket_addr;
  temp_socket_addr.sin_family = AF_INET;
  temp_socket_addr.sin_port = htons(CLIENT_RECEIVE_CONNECTION_PORT);
  temp_socket_addr.sin_addr.s_addr = INADDR_ANY;
  bzero(&(temp_socket_addr.sin_zero), 8);
  int optval = 1;
  setsockopt(temp_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));


  bind(temp_socket, (struct sockaddr *)&temp_socket_addr, sizeof(temp_socket_addr));
  
  // Listen in TEMP socket to create SYNC Data socket
  listen(temp_socket,SYNC_SOCKET_QUEUE_CAPACITY);

  // Accept SYNC Data socket
  sockaddr_in server_sync_socket_address;
  socklen_t server_sync_socket_address_len;
  int sync_data_communication_socket = accept(temp_socket, (struct sockaddr *)&server_sync_socket_address, &server_sync_socket_address_len);

    clientStateInformation->sync_data_communication_socket = sync_data_communication_socket;
    close(temp_socket);
}

void* serverAPIWatcher(void* clientStateInformation_arg){
    ClientStateInformation* clientStateInformation = (ClientStateInformation*)clientStateInformation_arg;
    while(clientStateInformation->is_connected){
        if(0){
            getCurrentRM();
            reconectInfoSock(clientStateInformation);
            reconectDataSock(clientStateInformation);
            
        }
    }

    return NULL;
}

int sockfd;
const char* multicast_ip = "224.0.0.1";
int port = 8888;

void createSocket(){
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
    close(sockfd);

    std::cout << "Waiting for multicast data..." << std::endl;
    char buffer[1024] = { 0 };
    int length = sizeof(localaddr);

    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&localaddr, (socklen_t*)&length);
    std::cout << buffer << std::endl;

}

#endif