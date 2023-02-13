#ifndef __UP_DOWNLOAD_HPP
#define __UP_DOWNLOAD_HPP

#include "userTerminalFunctions.hpp"
#include "errorHandling.hpp"

void single_transfer(string server, string file_path, bool download){
    ClientStateInformation clientStateInformation;
    clientStateInformation.running_in_server_host = false;
    clientStateInformation.is_syncronization_active = false;
    clientStateInformation.is_user_logged = false;
    clientStateInformation.is_connected = true;
    clientStateInformation.only_download = download;
    clientStateInformation.only_upload = !download;

    // Create INFO Data Communication Sockets
    int info_data_communication_socket = socket(AF_INET, SOCK_STREAM, 0);
    clientStateInformation.info_data_communication_socket = info_data_communication_socket;

    int optval = 1;
    setsockopt(info_data_communication_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    if(info_data_communication_socket == -1)
        pError("\a  ##Error on INFO data communication socket creation!");


    // Localize Server Host
    struct hostent *dataBag_server_host;
    struct in_addr ip_address; 

    ip_address.s_addr = inet_addr(server.c_str());
    dataBag_server_host = gethostbyaddr(&ip_address, sizeof(ip_address), AF_INET);

    if(dataBag_server_host == NULL)
        pError("\a  ##Failure: Can't localize server address!");   

    // Connect Info Data Communication Sockets
    struct sockaddr_in server_sentinel_socket_addr; 
    server_sentinel_socket_addr.sin_family = AF_INET;
    server_sentinel_socket_addr.sin_port = htons(SENTINEL_SOCKET_PORT);
    server_sentinel_socket_addr.sin_addr = *((struct in_addr*)dataBag_server_host->h_addr_list[0]);
    bzero(&(server_sentinel_socket_addr.sin_zero), 8);
    
    if(connect(info_data_communication_socket, (struct sockaddr *)&server_sentinel_socket_addr, sizeof(server_sentinel_socket_addr) ) < 0 )
        pError("\a  ##Failure: No server return for attemp of INFO Data Communication Socket conection!");

    userTerminal_login(&clientStateInformation);
    if(clientStateInformation.is_user_logged == true){
        ClientRequestDatagram clientRequest;
        ServerRequestResponseDatagram serverResponse;
        FileMetadata fileMetadata;
        int bytes_number;

        strcpy(fileMetadata.name, file_path.c_str());

        if(clientStateInformation.only_upload == true){
            // Request
            clientRequest.requisition_type = CLIENT_DATAGRAM_ONLY_UPLOAD;
            bytes_number = write(clientStateInformation.info_data_communication_socket, &clientRequest, REQUEST_DATAGRAM_SIZE);
            if(bytes_number == -1){
                cout << TERMINAL_TEXT_COLOR_RED;
                cout << "\a\t  ## Couldn't contact server via ";
                cout << TERMINAL_TEXT_COLOR_BLUE;
                cout << "INFO SOCKET";
                cout << TERMINAL_TEXT_COLOR_RED;
                cout << "!" << endl;
                cout << TERMINAL_TEXT_SETTING_RESET;
                return;
            }
        }else if(clientStateInformation.only_download == true){

        }
    }
}

#endif // __UP_DOWNLOAD_HPP
