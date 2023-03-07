#define FOLDER_H
#ifdef FOLDER_H
#pragma once

#include <string>
#include <vector>
#include "File.h"

class Folder
{
public:
    explicit Folder(std::string name);
    ~Folder();

    std::string getName();
    void setName(std::string name);
    void addFile(File* file);
    void addFolder(Folder* folder);
    std::vector<File*> getFiles();
    std::vector<Folder*> getFolders();
    int getContents();

private:
    std::string name;
    std::vector<File*> files;
    std::vector<Folder*> subfolders;
    int contents;
};

#endif //FOLDER_H