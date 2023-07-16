#define FOLDER_H
#ifdef FOLDER_H
#pragma once

#include <string>
#include <vector>
#include <File.h>

class Folder
{
public:
    explicit Folder(std::string Name);
    ~Folder();

    std::string getName();
    void setName(std::string folderName);
    void addFile(File* file);
    void addFolder(Folder* folder);
    std::vector<File*> getFiles();
    std::vector<Folder*> getFolders();
    uint64_t getContents();

private:
    std::string name;
    std::vector<File*> files;
    std::vector<Folder*> subfolders;
    uint64_t contents;
};

#endif //FOLDER_H