#include <iostream>

#include "globalMacros.hpp"

using namespace std;

class RequiredFolder{
    string path;
    string alias;

    public:
    RequiredFolder(string,string);
    ~RequiredFolder(){}
    string getPath(){return this->path;}
    string getAlias(){return this->alias;}  
};

RequiredFolder::RequiredFolder(string path, string alias){
    this->path = path;
    this->alias = alias;
}

