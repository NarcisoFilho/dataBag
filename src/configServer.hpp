#ifndef __CONFIG_SERVER_HPP
#define __CONFIG_SERVER_HPP

#include <iostream>
#include <list>

#include "global_definitions.hpp"
#include "RequiredFolder.hpp"


using namespace std;


void configServer();
void configFolderStructure();


void configServer(){
    configFolderStructure();
}

void configFolderStructure(){
    list<RequiredFolder> requiredFolders;
    requiredFolders.push_back(RequiredFolder(TEMP_FOLDER, stringfy(TEMP_FOLDER)));
    requiredFolders.push_back(RequiredFolder(DB_USERS_DATA_FOLDER, stringfy(DB_USERS_DATA_FOLDER)));

    // Create Essential Folders
    for(auto folder: requiredFolders){
        try{
            if(filesystem::create_directories(folder.getPath()))
            cout << "  ** " << folder.getAlias() << " Folder Created: " << endl;
        }catch(filesystem::filesystem_error &e){
            pError("  ## Can't create " +  folder.getAlias() + " Folder!");
        }
    }
}



#endif // __CONFIG_SERVER_HPP