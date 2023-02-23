#define DEARCHIVER_H
#ifdef DEARCHIVER_H
#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <filesystem>
#include <string.h>

#include <Folder.h>
#include <File.h>

class Dearchiver
{
public:
    Dearchiver(std::string archived_file);
    ~Dearchiver();

    void dearchive();

private:
    std::string archived_file;
};

#endif //DEARCHIVER_H