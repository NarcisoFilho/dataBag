#ifndef __GLOBAL_DEFINITIONS_HPP
#define __GLOBAL_DEFINITIONS_HPP

// REQUIRED FOLDERS
#define APP_FOLDER "~/dataBag" 
#define SYNCRONIZE_FOLDER "~/sync_dir" 
#define TEMP_FOLDER APP_FOLDER"/temp" 
#define DB_USERS_DATA_FOLDER APP_FOLDER"/DB/users_data/"

// DataBag
#define DATABAG_VERSION 0.1

// OS ENVIROMENT 

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
#define SERVER_SENTINEL_TERMINAL 	        	"serversentinelTerminal"
#define SERVER_REQUESTS_MAILBOX_TERMINAL	    "serverrequestsReceiverTerminal"
#define SERVER_DB_WATCHER_TERMINAL 		        "serverDBWatcherTerminal"
#define SERVER_DATA_HARBOR_TERMINAL 		    "serverDataHarborTerminal"
#define CLIENT_CONTROLER_TERMINAL 		        "clientControlerTerminal"
#define CLIENT_SYNC_DIR_WATCHER_TERMINAL 		"clientFilesWatcherTerminal"
#define CLIENT_DATA_HARBOR_TERMINAL 	        "clientDataHarborTerminal"

// SYNC MODULE
#define EVENTS_INOTIFY_BUFFER_LEN (1024 * 100)
#define MAX_FILE_NAME_SIZE 150
#define MAX_SYNC_LIST_SIZE 2000

//DB
#define DEFAULT_FOLDER_PERMISSION 0755 // The own user, group and others

// Close Server
#define FILE_OR_FOLDER_TO_CLOSE_SERVER "./closeServer"
#endif