#ifndef __TERMINAL_HANDLE_HPP
#define __TERMINAL_HANDLE_HPP

#include <iostream>
#include <fstream>
#include <list>
#include <set>
// #include <initialer_>
#include <vector>
#include <cstdarg>
#include <string>

using namespace std;

#define TERMINAL_TEXT_COLOR_BLACK "\033[1;30m"
#define TERMINAL_TEXT_COLOR_RED "\033[1;31m"
#define TERMINAL_TEXT_COLOR_GREEN "\033[1;32m"
#define TERMINAL_TEXT_COLOR_LIGHT_GREEN "\033[0;32m"
#define TERMINAL_TEXT_COLOR_YELLOW "\033[1;33m"
#define TERMINAL_TEXT_COLOR_BLUE "\033[1;34m"
#define TERMINAL_TEXT_COLOR_MAGENTA "\033[1;35m"
#define TERMINAL_TEXT_COLOR_CYAN "\033[1;36m"
#define TERMINAL_TEXT_COLOR_WHITE "\033[1;37m"
#define TERMINAL_TEXT_SETTING_RESET "\033[1;0m"


// Prototypes
void clearTerminal(string);
list<string> tokenizer(string);


void clearTerminal(string terminal){
    string cmd = " clear > " + terminal;
    system(cmd.c_str()); 
}

template<typename T1, typename T2, typename T3, typename T4>
void sendMessageToTerminal(ofstream &tty, T1 msg_arg, T2 object_arg, T3 target_arg, T4 source_arg = ""){
    string msg = msg_arg;
    string object = object_arg;
    string target = target_arg;
    string source = source_arg;
    
    const set<string> operationMarkerTokens = {">>>", "<<<", "++", "--", ">##", "##<"};
    list<string> tokens;
    auto mainMsgColor = TERMINAL_TEXT_SETTING_RESET;
    auto tokenColor = TERMINAL_TEXT_SETTING_RESET;

    tokens = tokenizer(msg);
    if( find(tokens.begin(), tokens.end(), "##") != tokens.end() ){
        mainMsgColor = TERMINAL_TEXT_COLOR_RED;
    }else if(find(tokens.begin(), tokens.end(), "**") != tokens.end()){
        mainMsgColor = TERMINAL_TEXT_SETTING_RESET;
    }else if(find(tokens.begin(), tokens.end(), "METADATA") != tokens.end()){
        mainMsgColor = TERMINAL_TEXT_SETTING_RESET;
    }else if(find(tokens.begin(), tokens.end(), "DELETATION") != tokens.end()){
        mainMsgColor = TERMINAL_TEXT_COLOR_YELLOW;
    }else if(find(tokens.begin(), tokens.end(), ">>>") != tokens.end()){
        mainMsgColor = TERMINAL_TEXT_COLOR_GREEN;
    }else if(find(tokens.begin(), tokens.end(), "<<<") != tokens.end()){
        mainMsgColor = TERMINAL_TEXT_COLOR_GREEN;
    }else if(find(tokens.begin(), tokens.end(), "++") != tokens.end()){
        mainMsgColor = TERMINAL_TEXT_COLOR_GREEN;
    }else if(find(tokens.begin(), tokens.end(), "--") != tokens.end()){
        mainMsgColor = TERMINAL_TEXT_COLOR_YELLOW;
    }else{
        mainMsgColor = TERMINAL_TEXT_SETTING_RESET;
    }

    for(string currentToken : tokens){
        if(currentToken == "$o"){
            currentToken = object;
            tokenColor = TERMINAL_TEXT_COLOR_BLUE;
        }else if(currentToken == "$s"){
            currentToken = source;
            tokenColor = TERMINAL_TEXT_COLOR_CYAN;
        }else if(currentToken == "$t"){
            currentToken = target;
            tokenColor = TERMINAL_TEXT_COLOR_CYAN;
        }else{
            tokenColor = mainMsgColor;
        }
        
        tty << tokenColor << currentToken << ' ';
    }

    tty << TERMINAL_TEXT_SETTING_RESET << endl;
}

string getTerminalColorByAlias(string color_alias){
    if( color_alias.compare("black") == 0 )
        return TERMINAL_TEXT_COLOR_BLACK;
    else if( color_alias.compare("green") == 0 )
        return TERMINAL_TEXT_COLOR_GREEN;
    else if( color_alias.compare("light-green") == 0 )
        return TERMINAL_TEXT_COLOR_LIGHT_GREEN;
    else if( color_alias.compare("yellow") == 0 )
        return TERMINAL_TEXT_COLOR_YELLOW;
    else if( color_alias.compare("blue") == 0 )
        return TERMINAL_TEXT_COLOR_BLUE;
    else if( color_alias.compare("magenta") == 0 )
        return TERMINAL_TEXT_COLOR_MAGENTA;
    else if( color_alias.compare("cyan") == 0 )
        return TERMINAL_TEXT_COLOR_CYAN;
    else if( color_alias.compare("white") == 0 )
        return TERMINAL_TEXT_COLOR_WHITE;
    
    return color_alias;
}

int getMessageArgumentsNumber(string msg){
    int num_args = 0;
    for( int i = 0 ; i < msg.size() ; i++)
        if( msg[i] == '%')
            if( msg[max(0,i-1)] != '%' && msg[min((int)msg.size(),i+1)] != '%' )
                num_args++;

    return num_args;
}
// void sendMessageToTerminal(ofstream &tty, char *mainColor, char *message, ...){
//     string message_s = message;
//     string mainColor_s = getTerminalColorByAlias(string(mainColor));
//     list<string> tokens = tokenizer(message_s);
//     int nmr_args = getMessageArgumentsNumber(message_s);
//     va_list args;
    
//     va_start(args, nmr_args);

//     auto tokenColor = mainColor_s;
//     for(string currentToken : tokens){
//         tokenColor = mainColor_s;
//         if(currentToken == "%bk"){
//             currentToken = va_arg(args, char*);
//             tokenColor = TERMINAL_TEXT_COLOR_BLACK;
//         }else if(currentToken == "%r"){
//             currentToken = va_arg(args, char*);
//             tokenColor = TERMINAL_TEXT_COLOR_RED;
//         }else if(currentToken == "%g"){
//             currentToken = va_arg(args, char*);
//             tokenColor = TERMINAL_TEXT_COLOR_GREEN;
//         }else if(currentToken == "%lg"){
//             currentToken = va_arg(args, char*);
//             tokenColor = TERMINAL_TEXT_COLOR_LIGHT_GREEN;
//         }else if(currentToken == "%y"){
//             currentToken = va_arg(args, char*);
//             tokenColor = TERMINAL_TEXT_COLOR_YELLOW;
//         }else if(currentToken == "%b"){
//             currentToken = va_arg(args, char*);
//             tokenColor = TERMINAL_TEXT_COLOR_BLUE;
//         }else if(currentToken == "%m"){
//             currentToken = va_arg(args, char*);
//             tokenColor = TERMINAL_TEXT_COLOR_MAGENTA;
//         }else if(currentToken == "%c"){
//             currentToken = va_arg(args, char*);
//             tokenColor = TERMINAL_TEXT_COLOR_CYAN;
//         }else if(currentToken == "%w"){
//             currentToken = va_arg(args, char*);
//             tokenColor = TERMINAL_TEXT_COLOR_WHITE;
//         }
        
//         tty << tokenColor << currentToken << ' ';
//     }

//     va_end(args);

//     tty << TERMINAL_TEXT_SETTING_RESET << endl;
// }

list<string> tokenizer(string msg){
    list<string> tokens;
    string next_token;
    
    while(  msg.front() != '\0'  ){
        msg = msg.substr( msg.find_first_not_of(' ') );             // Remove spaces
        next_token = msg.substr(0, ( msg.find_first_of(" \0") ));   // Get token from msg
        tokens.push_back(next_token);                                    // Push token in tokens list
        msg = msg.substr( next_token.size() );                      // Remove current token from msg
    }

    return tokens;
}

#endif // __TERMINAL_HANDLE_HPP