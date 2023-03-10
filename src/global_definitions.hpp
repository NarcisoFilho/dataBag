#ifndef __GLOBAL_DEFINITIONS_HPP
#define __GLOBAL_DEFINITIONS_HPP

// DataBag
#define DATABAG_VERSION 0.1

// OS ENVIROMENT 
#define SYNCRONIZE_FOLDER "~/sync_dir" 
#define TEMP_FOLDER "~/dataBag/temp" 

// SOCKETS
#define SENTINEL_SOCKET_PORT 7777
#define SENTINEL_SOCKET_QUEUE_CAPACITY 200
#define CLIENT_RECEIVE_CONNECTION_PORT 8888
#define SYNC_SOCKET_QUEUE_CAPACITY 10
#define DATA_COMMUNICATION_BUFFER_CAPACITY 1024

// DATAGRAM COMMUNICATION
#define REQUEST_DATAGRAM_SIZE sizeof(ClientRequestDatagram)
#define REQUEST_RESPONSE_DATAGRAM_SIZE sizeof(ServerRequestResponseDatagram)

#define CLIENT_REQUEST_QUIT                     0
#define CLIENT_REQUEST_LOGIN                    1
#define CLIENT_REQUEST_REGISTER                 2
#define CLIENT_REQUEST_START                    3
#define CLIENT_REQUEST_STATUS                   4
#define CLIENT_REQUEST_STOP                     5
#define CLIENT_DATAGRAM_SYNC_STATE_LIST         6
#define CLIENT_DATAGRAM_ONLY_UPLOAD             10
#define CLIENT_DATAGRAM_ONLY_DOWLOAD            11

#define SERVER_SYNC_ORDER_RECEIVE_DATAGRAM      7
#define SERVER_SYNC_ORDER_SEND_DATAGRAM         8

#define SYNC_DATAGRAM                           9

#define MAX_CLIENT_REQUEST_CODE CLIENT_REQUEST_STOP


// TERMINAL COLOURS
#define TERMINAL_TEXT_COLOR_BLACK "\033[1;30m"
#define TERMINAL_TEXT_COLOR_RED "\033[1;31m"
#define TERMINAL_TEXT_COLOR_GREEN "\033[1;32m"
#define TERMINAL_TEXT_COLOR_YELLOW "\033[1;33m"
#define TERMINAL_TEXT_COLOR_BLUE "\033[1;34m"
#define TERMINAL_TEXT_COLOR_MAGENTA "\033[1;35m"
#define TERMINAL_TEXT_COLOR_CYAN "\033[1;36m"
#define TERMINAL_TEXT_COLOR_WHITE "\033[1;37m"
#define TERMINAL_TEXT_SETTING_RESET "\033[1;0m"

// TERMINAL FOR OUTPUTS
#define TERMINAL_SERVER_SENTINEL "/dev/pts/2"
#define TERMINAL_SERVER_INFO_SOCKET "/dev/pts/2"
#define TERMINAL_SERVER_DB_WATCHER "/dev/pts/2"
#define TERMINAL_SERVER_SYNC_MODULE "/dev/pts/2"
#define DEF_TERMINAL_CLIENT_USER_TERMINAL "/dev/pts/3"
#define DEF_TERMINAL_CLIENT_FOLDER_WATCHER "/dev/pts/3"
#define DEF_TERMINAL_CLIENT_SYNC_MODULE "/dev/pts/3"
// #define TERMINAL_SERVER_SENTINEL "/dev/pts/1"
// #define TERMINAL_SERVER_INFO_SOCKET "/dev/pts/2"
// #define TERMINAL_SERVER_DB_WATCHER "/dev/pts/3"
// #define TERMINAL_SERVER_SYNC_MODULE "/dev/pts/4"
// #define DEF_TERMINAL_CLIENT_USER_TERMINAL "/dev/pts/5"
// #define DEF_TERMINAL_CLIENT_FOLDER_WATCHER "/dev/pts/6"
// #define DEF_TERMINAL_CLIENT_SYNC_MODULE "/dev/pts/7"
char TERMINAL_CLIENT_USER_TERMINAL[20];
char TERMINAL_CLIENT_FOLDER_WATCHER[20];
char TERMINAL_CLIENT_SYNC_MODULE[20];

// SYNC MODULE
#define EVENTS_INOTIFY_BUFFER_LEN (1024 * 100)
#define MAX_FILE_NAME_SIZE 150
#define MAX_SYNC_LIST_SIZE 2000

//DB
#define DB_USERS_DATA_FOLDER "~/dataBag/db/users_data/"
#define DB_USERS_DATA_FOLDER_PERMISSION 0755 // THe own user, group and others

// Close Server
#define FILE_OR_FOLDER_TO_CLOSE_SERVER "./closeServer"
#endif