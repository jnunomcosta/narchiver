#define ARCHIVER_H
#ifdef ARCHIVER_H
#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <filesystem>
#include <string.h>

#include <Folder.h>
#include <File.h>

class Archiver
{
public:
    Archiver(std::string folder_path, std::string archive_path);
    ~Archiver();

    void archive();

private:
    std::string folder_path, archive_path;
    std::map<std::string, std::vector<File>> files;
    int total_files, files_processed;
    int getfiles(std::string folder_path);
};

#endif //ARCHIVER_H