#ifndef __SERVERS_API_HPP
#define __SERVERS_API_HPP


#include <iostream>
#include <vector>

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
void createMulticastSocket();
void sendMulticastMessage();
void receiveMulticastMessage();
void* listenGroupModule(void*);


vector<ServerReplica> servers;
ServerReplica currentManager;
int multicastSocket;

void introduceYourSelf(){
    //
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

void createMulticastSocket(){

}

void sendMulticastMessage(){

}

void receiveMulticastMessage(){

}

void* listenGroupModule(void* arg){

}



#endif // __SERVERS_API_HPP