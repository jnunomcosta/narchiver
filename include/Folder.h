#define FOLDER_H
#ifdef FOLDER_H
#pragma once

#include <string>
#include <vector>
#include <File.h>

class Folder
{
public:
    Folder(std::string);
    ~Folder();

    std::string getName();
    void setName(std::string);
    void addFile(File&);
    void addFolder(Folder&);

private:
    std::string name;
    std::vector<File> files;
    std::vector<Folder> subfolders;
};

#endif //FOLDER_H