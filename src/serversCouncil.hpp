#ifndef __SERVERS_API_HPP
#define __SERVERS_API_HPP


#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ClientDeviceConected.hpp"

using namespace std;

typedef struct {
    string ip;
    int rank;
    bool isRM;
    bool ativo;
} ServerReplica;

/// Prototypes
void introduceYourSelf();
vector<ServerReplica> getReplicasList();
ServerReplica findManager();
int createServersMulticastSocket();
void sendMulticastMessage(string);
string receiveMulticastMessage();
void* councilActionModule(void*);


vector<ServerReplica> servers;
ServerReplica currentManager;
int serverChanelMulticastSocket;
int frontEndChanelMulticastSocket;
int socketManagerDirect;
struct sockaddr_in mcast_addr;

const char serversGroup[] = "225.0.0.37";
const char frontEndGroup[] = "225.0.0.4";

void* councilActionModule(void* arg){
    createServersMulticastSocket();
    introduceYourSelf();
    //waitManagerResponse
    //conect direct socket to manager

    while(1){
        //listendirectmanagersocket
        // if demorou demais o manager caiu
        //       portanto eleicao
        //else switch from manager order
        //
        // if smtg do smtg
        // if update servers list do s
        // if receive file do smtg2
        // if delete file do smtg2
        // 
    }
}

void connectManagerDirectSocket(string ip){

}

void introduceYourSelf(){
    // 

    // Send to

    servers = getReplicasList();
    currentManager = findManager();
}

vector<ServerReplica> getReplicasList(){
    vector<ServerReplica> currentList;
    ServerReplica r1, r2;
    r1.rank = 7;    
    r2.rank = 9;    
    currentList.push_back(r1);
    currentList.push_back(r2);

    return currentList;
}

void multicastReplicaList(){

}

ServerReplica findManager(){
    ServerReplica manager = {};
    for(auto server: servers){
        if(server.isRM)
            manager = server;
    }

    return manager;
}

int createServersMulticastSocket(){
    serverChanelMulticastSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // Set up multicast address
    mcast_addr.sin_family = AF_INET;
    mcast_addr.sin_addr.s_addr = inet_addr(serversGroup);
    mcast_addr.sin_port = htons(12345);
   
    // Bind to the multicast address
    bind(serverChanelMulticastSocket, (struct sockaddr*)&mcast_addr, sizeof mcast_addr);

    // Set socket options
    int optval = 1;
    setsockopt(serverChanelMulticastSocket, SOL_SOCKET, SO_BROADCAST, &optval, sizeof optval);
}

int createFrontendMulticastSocket(){
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

vector<ServerReplica> splitReplicas(char input[1024]) {
    vector<string> resultInString;
    char *ptr;
    ptr = strtok(input, ";");
    while (ptr != NULL) {
        resultInString.push_back(string(ptr));
        ptr = strtok(NULL, ";");
    }
    
    vector<ServerReplica> replicas;

    for(auto rInString: resultInString){
        replicas.push_back(deserializeServer(rInString));
    }

    return replicas;
}

ServerReplica deserializeServer(const string &str)
{
    ServerReplica replica;
    vector<string> parts;
    string part;

    for (char c : str)
    {
        if (c == '#')
        {
            parts.push_back(part);
            part = "";
        }
        else
        {
            part.push_back(c);
        }
    }
    parts.push_back(part);

    replica.ip = parts[0];
    replica.rank =  stoi(parts[1]);
    replica.isRM = (parts[2] == "1") ? true : false ;
    replica.ativo = (parts[3] == "1") ? true : false ;
    return replica;
}

string serializeServer(ServerReplica server){
    string serverEncoded = "";

    serverEncoded.append(server.ip);
    serverEncoded.append(to_string(server.rank));
    serverEncoded.append(to_string(static_cast<int>(server.isRM)));
    serverEncoded.append(to_string(static_cast<int>(server.ativo)));

    return serverEncoded;
}

string serializeServersList(){
    string serverList = "";
    
    for(auto serv: servers){
        serverList.append( serializeServer(serv) );
    }

    return serverList;
}
#endif // __SERVERS_API_HPP