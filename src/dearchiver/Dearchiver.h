#define DEARCHIVER_H
#ifdef DEARCHIVER_H
#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <filesystem>
#include <string.h>

class Dearchiver
{
public:
    Dearchiver(std::string archivedFile, std::string dearchivedFolder);
    ~Dearchiver();

    void dearchive();

private:
    std::string archived_file;
    std::string dearchived_folder;
};

#endif //DEARCHIVER_H
