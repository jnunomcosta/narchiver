#include <string>
#include <vector>
#include "File.h"
using namespace std;

#pragma once
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