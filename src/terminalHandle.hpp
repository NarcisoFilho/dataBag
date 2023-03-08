#ifndef __TERMINAL_HANDLE_HPP
#define __TERMINAL_HANDLE_HPP

#include <iostream>
#include <fstream>
#include <list>
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
void terminalPrint(ofstream&, string );
template<typename T1, typename T2, typename T3, typename T4> void terminalPrint(ofstream&, T1, T2, T3, T4);
list<string> tokenizer(string);
string getProbablyMainColor(list<string>);
string getTerminalColorByAlias(string);
string getTerminalColorByCode(string);
void clearTerminal(string);

// Functions
void terminalPrint(ofstream &tty, string msg){
    list<string> tokens = tokenizer(msg);
    auto initialColor = getProbablyMainColor(tokens);
    auto currrentColor = initialColor;

    for(string currentToken : tokens){
        if(currentToken[0] == '$'){
            currrentColor = getTerminalColorByAlias(currentToken);
        }else{
            tty << currrentColor << currentToken << ' ';
        }
    }

    tty << TERMINAL_TEXT_SETTING_RESET << endl;
}

template<typename T1, typename T2, typename T3, typename T4>
void terminalPrint(ofstream &tty, T1 msg_arg, T2 object_arg, T3 target_arg, T4 source_arg = ""){
    string msg = msg_arg;
    string object = object_arg;
    string target = target_arg;
    string source = source_arg;
    
    list<string> tokens = tokenizer(msg);
    auto mainMsgColor = getProbablyMainColor(tokes);
    auto tokenColor = mainMsgColor;

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

string getProbablyMainColor(list<string> tokens){
    if( find(tokens.begin(), tokens.end(), "##") != tokens.end() ){
        return TERMINAL_TEXT_COLOR_RED;
    }else if(find(tokens.begin(), tokens.end(), "**") != tokens.end()){
        return TERMINAL_TEXT_SETTING_RESET;
    }else if(find(tokens.begin(), tokens.end(), "METADATA") != tokens.end()){
        return TERMINAL_TEXT_SETTING_RESET;
    }else if(find(tokens.begin(), tokens.end(), "DELETATION") != tokens.end()){
        return TERMINAL_TEXT_COLOR_YELLOW;
    }else if(find(tokens.begin(), tokens.end(), ">>>") != tokens.end()){
        return TERMINAL_TEXT_COLOR_GREEN;
    }else if(find(tokens.begin(), tokens.end(), "<<<") != tokens.end()){
        return TERMINAL_TEXT_COLOR_GREEN;
    }else if(find(tokens.begin(), tokens.end(), "++") != tokens.end()){
        return TERMINAL_TEXT_COLOR_GREEN;
    }else if(find(tokens.begin(), tokens.end(), "--") != tokens.end()){
        return TERMINAL_TEXT_COLOR_YELLOW;
    }else{
        return TERMINAL_TEXT_SETTING_RESET;
    }
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

string getTerminalColorByCode(string code){
    if(code == "$bk"){
        return TERMINAL_TEXT_COLOR_BLACK;
    }else if(code == "$r"){
        return TERMINAL_TEXT_COLOR_RED;
    }else if(code == "$g"){
        return TERMINAL_TEXT_COLOR_GREEN;
    }else if(code == "$lg"){
        return TERMINAL_TEXT_COLOR_LIGHT_GREEN;
    }else if(code == "$y"){
        return TERMINAL_TEXT_COLOR_YELLOW;
    }else if(code == "$b"){
        return TERMINAL_TEXT_COLOR_BLUE;
    }else if(code == "$m"){
        return TERMINAL_TEXT_COLOR_MAGENTA;
    }else if(code == "$c"){
        return TERMINAL_TEXT_COLOR_CYAN;
    }else if(code == "$w"){
        return TERMINAL_TEXT_COLOR_WHITE;
    }else{
        return TERMINAL_TEXT_SETTING_RESET;
    }
}


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

void clearTerminal(string terminal){
    string cmd = " clear > " + terminal;
    system(cmd.c_str()); 
}

#endif // __TERMINAL_HANDLE_HPP