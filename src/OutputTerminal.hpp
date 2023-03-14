#ifndef __OUTPUT_TERMINAL__
#define __OUTPUT_TERMINAL__

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include "global_definitions.hpp"

using namespace std;

#define COLOR_BLACK "\033[1;30m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_LIGHT_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_WHITE "\033[1;37m"
#define SETTING_RESET "\033[1;0m"

class OutputTerminal{
    private:
    string terminalName;
    string ptsCode;
    ofstream tty;
    string currentColor;

    public:
    OutputTerminal(string);
    OutputTerminal(const OutputTerminal&);
    ~OutputTerminal();
    void print(string);
    void print(string, string);
    void printInline(string, string);
    template<typename T1, typename T2, typename T3, typename T4 = string> void print(T1, T2, T3, T4  = "");
    void clear();
    void close();

    private:
    list<string> tokenizer(string);
    string getProbablyMainColor(list<string>);
    string getTerminalColorByAlias(string);
    string getTerminalColorByCode(string);
    string openAndRegisterTerminal(string);
    bool openTTYFile();
    // string findOpendTerminal(string);
};

OutputTerminal::OutputTerminal(string terminalName){
    this->terminalName = terminalName;
    this->ptsCode = this->openAndRegisterTerminal(this->terminalName);
    this->openTTYFile();
}

OutputTerminal::OutputTerminal(const OutputTerminal& outputTerminalObject){
    this->currentColor = outputTerminalObject.currentColor;
    this->ptsCode = outputTerminalObject.ptsCode;
    this->terminalName = outputTerminalObject.terminalName;
    this->openTTYFile();
}

OutputTerminal::~OutputTerminal(){
    this->tty.close();
}

bool OutputTerminal::openTTYFile(){
    this->tty.open(this->ptsCode, ofstream::out | ofstream::app);
    return this->tty.is_open();
}

string OutputTerminal::openAndRegisterTerminal(string terminalName){
    string ptsRegisterFileName = string(APP_FOLDER) + "/." + terminalName.substr(0,7);

    system((string("") + "gnome-terminal -- $SHELL -c \" tty > "+ ptsRegisterFileName + "; exec $SHELL\"").c_str());
    
    ifstream ptsRegisterFile(ptsRegisterFileName);
    char ptsCode[50];
    ptsRegisterFile.getline(ptsCode,50);

    return ptsCode;
}

void OutputTerminal::print(string msg){
    list<string> tokens = this->tokenizer(msg);
     this->currentColor = this->getProbablyMainColor(tokens);

    for(string currentToken : tokens){
        if(currentToken[0] == '$'){
            this->currentColor = this->getTerminalColorByCode(currentToken);
        }else{
            tty << this->currentColor << currentToken << ' ';
        }
    }

    this->currentColor = SETTING_RESET;
    tty << this->currentColor << endl;    
}

void OutputTerminal::print(string msg, string color){
    this->printInline(msg, color);
    this->currentColor = SETTING_RESET;
    tty << this->currentColor << endl;
}

void OutputTerminal::printInline(string msg, string color){
    this->currentColor = this->getTerminalColorByAlias(color);        
    tty << this->currentColor << msg;
}

template<typename T1, typename T2, typename T3, typename T4>
void OutputTerminal::print(T1 msg_arg, T2 object_arg, T3 target_arg, T4 source_arg){
    string msg = msg_arg;
    string object = object_arg;
    string target = target_arg;
    string source = source_arg;
    
    list<string> tokens = this->tokenizer(msg);
    auto mainMsgColor = this->getProbablyMainColor(tokens);
    this->currentColor = mainMsgColor;

    for(string currentToken : tokens){
        if(currentToken == "$o"){
            currentToken = object;
            this->currentColor = TERMINAL_TEXT_COLOR_BLUE;
        }else if(currentToken == "$s"){
            currentToken = source;
            this->currentColor = TERMINAL_TEXT_COLOR_CYAN;
        }else if(currentToken == "$t"){
            currentToken = target;
            this->currentColor = TERMINAL_TEXT_COLOR_CYAN;
        }else{
            this->currentColor = mainMsgColor;
        }
        
        tty << this->currentColor << currentToken << ' ';
    }

    this->currentColor = SETTING_RESET;
    tty << this->currentColor << endl;
}

list<string> OutputTerminal::tokenizer(string msg){
    list<string> tokens;
    string next_token;
    
    while(  msg.front() != '\0'  ){
        msg = msg.substr( msg.find_first_not_of(' ') );             // Remove spaces
        next_token = msg.substr(0, ( msg.find_first_of(" \0") ));   // Get token from msg
        tokens.push_back(next_token);                               // Push token in tokens list
        msg = msg.substr( next_token.size() );                      // Remove current token from msg
    }

    return tokens;
}

string OutputTerminal::getProbablyMainColor(list<string> tokens){
    string mainColor = SETTING_RESET;
    
    for( auto it = tokens.begin(); it != tokens.end(); it++){
        if(*it=="##" || *it=="###")
            return COLOR_RED;
        else if(*it=="**" || *it=="***" || *it=="METADATA")
            return SETTING_RESET;
        else if(*it=="DELETATION" || *it=="--" || *it=="---")
            return COLOR_YELLOW;
        else if(*it==">>>" || *it=="<<<" || *it =="++" || *it =="+++")
            return COLOR_GREEN;
    }
    
    return mainColor;
}

string OutputTerminal::getTerminalColorByAlias(string color_alias){
    if( color_alias.compare("black") == 0 )
        return COLOR_BLACK;
    else if( color_alias.compare("green") == 0 )
        return COLOR_GREEN;
    else if( color_alias.compare("light-green") == 0 )
        return COLOR_LIGHT_GREEN;
    else if( color_alias.compare("yellow") == 0 )
        return COLOR_YELLOW;
    else if( color_alias.compare("blue") == 0 )
        return COLOR_BLUE;
    else if( color_alias.compare("magenta") == 0 )
        return COLOR_MAGENTA;
    else if( color_alias.compare("cyan") == 0 )
        return COLOR_CYAN;
    else if( color_alias.compare("white") == 0 )
        return COLOR_WHITE;
    else 
        return SETTING_RESET;
    
    return color_alias;
}

string OutputTerminal::getTerminalColorByCode(string code){
    if(code == "$bk"){
        return COLOR_BLACK;
    }else if(code == "$r"){
        return COLOR_RED;
    }else if(code == "$g"){
        return COLOR_GREEN;
    }else if(code == "$lg"){
        return COLOR_LIGHT_GREEN;
    }else if(code == "$y"){
        return COLOR_YELLOW;
    }else if(code == "$b"){
        return COLOR_BLUE;
    }else if(code == "$m"){
        return COLOR_MAGENTA;
    }else if(code == "$c"){
        return COLOR_CYAN;
    }else if(code == "$w"){
        return COLOR_WHITE;
    }else{
        return SETTING_RESET;
    }
}

void OutputTerminal::clear(){
    string cmd = " clear > " + this->ptsCode;
    system(cmd.c_str()); 
}

void OutputTerminal::close(){
    string cmd = " exit > " + this->ptsCode;
    system(cmd.c_str()); 
}

// void OutputTerminal::close(){
//     string cmd = " exit > " + this->ptsCode;
//     system(cmd.c_str());

    // vector<OutputTerminalId>::iterator it = OutputTerminal::openedTerminals.begin() + OutputTerminal::findTerminalOpendIndex(terminalName);
    // OutputTerminal::openedTerminals.erase(it);
// }

// string OutputTerminal::findOpendTerminal(string terminalName){
//     string ptsCode = "";
    
//     for(auto terminalId: OutputTerminal::openedTerminals){
//         if(terminalId.terminalName == terminalName){
//             ptsCode = terminalId.ptsCode;
//             break;
//         }
//     }

//     return ptsCode;
// }

// int OutputTerminal::findTerminalOpendIndex(string terminalName){
//     int index = 0;
//     for(auto terminalId: OutputTerminal::openedTerminals){
//         if(terminalId.terminalName == terminalName){
//             return index; 
//         }
//         index++;
//     }
//     return -1;
// }

#endif // __OUTPUT_TERMINAL__
