#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#include "errorHandling.hpp"
#include "userDataBag.hpp"
#include "serverCommunicationManager.hpp"
#include "global_definitions.hpp"
#include "terminalHandle.hpp"
#include "OutputTerminal.hpp"

#include "configServer.hpp"

using namespace std;

int main(){
    // Open terminals
    vector<OutputTerminal> terminals;    
    terminals.emplace_back(OutputTerminal(SERVER_REQUESTS_MAILBOX_TERMINAL));
    terminals.emplace_back(OutputTerminal(SERVER_DB_WATCHER_TERMINAL));
    terminals.emplace_back(OutputTerminal(SERVER_DATA_HARBOR_TERMINAL));

    // Config Server
    configServer();  

    

    // Create Sentinel Socket
    int servers_sentinel_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(servers_sentinel_socket == -1)
        pError("### \a Error on sentinel socket creation!");
    else
        cout << "  ** Server Sentinel Socket created successfully ..." << endl;

    // Settings
    int optval = 1;
    setsockopt(servers_sentinel_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // Bind Sentinel Socket
    struct sockaddr_in sentinel_server_socket_addr;
    sentinel_server_socket_addr.sin_family = AF_INET;
    sentinel_server_socket_addr.sin_port = htons(SENTINEL_SOCKET_PORT);
    sentinel_server_socket_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(sentinel_server_socket_addr.sin_zero), 8);

    if( bind(servers_sentinel_socket, (const sockaddr *)&sentinel_server_socket_addr, sizeof(sentinel_server_socket_addr)) < 0 )
        pError("### \a Error on sentinel socket binding!");
    else
        cout << "  ** Server Sentinel Socket binded to port ..."<< SENTINEL_SOCKET_PORT << " successfully" << endl;
    
    // Server's New Device Sentinel Service Thread Initialization
    pthread_t sentinelServiceThread;

    if( pthread_create( &sentinelServiceThread, NULL, serverSentinelModule, (void*)&servers_sentinel_socket) != 0 )
        pError("Error on initizalization of New Device Sentinel Service Thread");    
    else
        cout << "  ** 'New Device Sentinel' Service initialized successufully ..." << endl;

    // Close
    for(auto terminal : terminals)
        terminal.close();

    pthread_t closing_monitor_thread;
    volatile bool close_flag = false;
    pthread_create(&closing_monitor_thread, NULL, monitore_if_server_should_close, (void*)&close_flag);
    pthread_join(closing_monitor_thread, NULL);
    close(servers_sentinel_socket);
    return 0;
}
