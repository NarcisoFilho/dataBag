#ifndef __SERVER_REQUESTS_HPP
#define __SERVER_REQUESTS_HPP


#include <iostream>
#include <string>

using namespace std;

namespace ClientsRequests{
    enum{   
        QUIT    ,
        LOGIN   ,
        REGISTER,
        START   ,
        STATUS  ,
        STOP
    };

    const vector<string> REQUESTS_NAMES = {
        "CLIENT_REQUEST_QUIT",    
        "CLIENT_REQUEST_LOGIN",   
        "CLIENT_REQUEST_REGISTER",
        "CLIENT_REQUEST_START",   
        "CLIENT_REQUEST_STATUS",  
        "CLIENT_REQUEST_STOP"    
    };

    bool isRequestValid(int code){
        if(code < 0 || code >= REQUESTS_NAMES.size())
            return false;
        
        return true;
    }

    string getRequestName(int code){
        string requestName = "UNKNOWN request";

        if(isRequestValid(code))
            requestName =  REQUESTS_NAMES[code];
        
        return requestName;
    }
}


#endif // __SERVER_REQUESTS_HPP
