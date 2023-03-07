#include "Folder.h"

Folder::Folder(std::string name)
{
    this->name = name;
    this->files = std::vector<File*>();
    this->subfolders = std::vector<Folder*>();
    this->contents = 0;
}

Folder::~Folder()
{
    //Delete Files
    for(auto file : this->files)
    {
        if(file != nullptr)
        {
            delete file;
        }  
    }

    //Delete Subfolders
    for(auto folder : this->subfolders)
    {
        if(folder != nullptr)
        {
            delete folder;
        }
        
    }
}

std::string Folder::getName() {
    return this->name;
}

void Folder::setName(std::string name) {
    this->name = name;
}

void Folder::addFile(File* file) {
    this->files.push_back(file);
    contents++;
}

void Folder::addFolder(Folder* folder) {
    this->subfolders.push_back(folder);
    contents++;
}

std::vector<File*> Folder::getFiles()
{
    return this->files;
}

std::vector<Folder*> Folder::getFolders()
{
    return this->subfolders;
}

int Folder::getContents()
{
    return contents;
}