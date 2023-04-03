#ifndef __FRONTEND_HPP
#define __FRONTEND_HPP

#include <iostream>
#include <cstring>
#include <unistd.h>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "global_definitions.hpp"
#include "errorHandling.hpp"

using namespace std;

/// Prototypes
int createINFOSocket(bool = false);
int createSYNCSocket();
void requestRmIP();
const char* getRmIp();


char rmIP[50] = "";
int serverChanelMulticastSocket;
int socketManagerDirect;
struct sockaddr_in mcast_addr;
const char serversGroup[] = "225.0.0.37";
const char frontEndGroup[] = "225.0.0.4";

int createINFOSocket(bool isReconection){
    int info_communication_socket = socket(AF_INET, SOCK_STREAM, 0);
    int optval = 1;
    
    setsockopt(info_communication_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if(info_communication_socket == -1)
        pError("\a  ##Error on INFO data communication socket creation!");
    else
        cout << "  ** INFO Data Socket created successfully ..." << endl;

    // Localize Server Host
    // struct hostent *dataBag_server_host;
    // struct in_addr ip_address; 
    if(!isReconection)
        strcpy(rmIP, getRmIp());
    
    // ip_address.s_addr = inet_addr(rmIP);
    // dataBag_server_host = gethostbyaddr(&ip_address, sizeof(ip_address), AF_INET);

    // Get IP address of computer
    char ip_address[50];
    strcpy(ip_address, rmIP);

    // Set address and port
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(80);  // Listen on port 80
    inet_pton(AF_INET, ip_address, &server.sin_addr);

    // if(dataBag_server_host == NULL)
    //     pError("\a  ##Failure: Can't localize server address!");   
    // else
    //     cout << "  ** Server address localized successfully!" << endl;

    // Connect Info Data Communication Sockets
    struct sockaddr_in server_sentinel_socket_addr; 
    server_sentinel_socket_addr.sin_family = AF_INET;
    server_sentinel_socket_addr.sin_port = htons(SENTINEL_SOCKET_PORT);
    // server_sentinel_socket_addr.sin_addr = *((struct in_addr*)dataBag_server_host->h_addr_list[0]);
    inet_pton(AF_INET, ip_address, &server_sentinel_socket_addr.sin_addr);
    bzero(&(server_sentinel_socket_addr.sin_zero), 8);

    if(connect(info_communication_socket, (struct sockaddr *)&server_sentinel_socket_addr, sizeof(server_sentinel_socket_addr) ) < 0 )
        pError("\a  ##Failure: No server return for attemp of INFO Data Communication Socket conection!");   

    return info_communication_socket;
}

int createSYNCSocket(){  
    // TEMP socket to listen SYNC Data socket
    int temp_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in  temp_socket_addr;
    temp_socket_addr.sin_family = AF_INET;
    temp_socket_addr.sin_port = htons(CLIENT_RECEIVE_CONNECTION_PORT);
    temp_socket_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(temp_socket_addr.sin_zero), 8);
    int optval = 1;
    setsockopt(temp_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if(bind(temp_socket, (struct sockaddr *)&temp_socket_addr, sizeof(temp_socket_addr)) == -1)
        pError("\a### Error on TEMP socket binding!");
    else
        cout << "  ** TEMP Socket binded to port "<< CLIENT_RECEIVE_CONNECTION_PORT << " successfully" << endl;
    
    // Listen in TEMP socket to create SYNC Data socket
    if(listen(temp_socket,SYNC_SOCKET_QUEUE_CAPACITY) == -1)
        pError("\a  ##Failure: Can't listen on TEMP socket to recieve SYNC socket!");   
    else
        cout << "  ** TEMP socket listen: Awaiting for server request for SYNC socket ..." << endl;

    // Accept SYNC Data socket
    sockaddr_in server_sync_socket_address;
    socklen_t server_sync_socket_address_len;
    int sync_data_communication_socket = accept(temp_socket, (struct sockaddr *)&server_sync_socket_address, &server_sync_socket_address_len);

    if(sync_data_communication_socket == -1)
        pError("\a  ##Error on SYNC data communication socket creation(acceptance)!");
    else
        cout << "  ** SYNC Data Socket created(accepted) succesrequestRmIPsfully ..." << endl;

    close(temp_socket);
    return sync_data_communication_socket;
}

// void requestRmIP(){
//     sendMulticastMessage("requestRmIP");
//     string response = receiveMulticastMessage();

//     while(response.substr(4) != "RmIP"){
//         response = receiveMulticastMessage();
//     }

//     response = response.substr(4);
//     strcpy(rmIP, response.c_str());
// }

const char* getRmIp(){
    static char mainServerIP[50] = "";
    strcpy(mainServerIP, "127.0.0.1");
    // strcpy(mainServerIP, "172.18.0.1");
    // strcpy(mainServerIP, "192.168.1.101");
    // strcpy(mainServerIP, "172.25.61.213");
    // strcpy(mainServerIP, "127.0.1.1");
    // strcpy(mainServerIP, "127.0.1.1");
    
    return (const char*)mainServerIP;

    // requestRmIP();
    // return (const char*) rmIP;
}
#include <thread>
void* frontendModule(void* arg){
    ClientStateInformation *clientStateInformation = (ClientStateInformation*)arg;
    string serverMessage;

    // listen multicast sock
    // while(clientStateInformation->is_connected){
    //     // serverMessage = receiveMulticastMessage();

    //     // if(serverMessage[0] == 's'){
    //     //     //nothing
    //     // }else if(serverMessage[0] == 'c'){
    //     //     strcpy(rmIP, serverMessage.substr(1).c_str());
    //     //     clientStateInformation->info_communication_socket = createINFOSocket();
    //     //     clientStateInformation->sync_data_communication_socket = createSYNCSocket();            
    //     // }
        cout << " \n>>>>>> I will change the server" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(13));

        strcpy(rmIP, "192.168.1.101");
        clientStateInformation->info_communication_socket = createINFOSocket();
        clientStateInformation->sync_data_communication_socket = createSYNCSocket();            
        
        cout << "\n>>> Server changed" << endl;
    // }

    return NULL;

}

int createServersMulticastSocket(){
    // Create a socket
    serverChanelMulticastSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // Set up multicast address
    mcast_addr.sin_family = AF_INET;
    mcast_addr.sin_addr.s_addr = inet_addr(frontEndGroup);
    mcast_addr.sin_port = htons(12345);
   
    // Bind to the multicast address
    bind(serverChanelMulticastSocket, (struct sockaddr*)&mcast_addr, sizeof mcast_addr);

    // Set socket options
    int optval = 1;
    setsockopt(serverChanelMulticastSocket, SOL_SOCKET, SO_BROADCAST, &optval, sizeof optval);

    return serverChanelMulticastSocket;
}

void sendMulticastMessage(string message){
    // Send the message
    char buffer[1024];
    strcpy(buffer, message.c_str());
    sendto(serverChanelMulticastSocket, buffer, strlen(buffer), 0, (struct sockaddr*)&mcast_addr, sizeof mcast_addr);
}

string receiveMulticastMessage(){
    char buffer[1024];
    
    // Receive the message
    int count = recvfrom(serverChanelMulticastSocket, buffer, 1024, 0, NULL, NULL);
    buffer[count] = '\0';

    // cout << buffer << endl;
    string message = buffer;
    return message;
}

#endif // __FRONTEND_HPP