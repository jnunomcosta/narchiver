#define ARCHIVER_H
#ifdef ARCHIVER_H
#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
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
    Folder* folder_archive;
};

void writeFolderByteData(FILE* arch_file_pointer, Folder* folder, std::string folder_path);
void writeFileByteData(FILE* arch_file_pointer, File* file);
int loadFiles(std::string base_path, std::string current_path, Folder* base_folder);
std::vector<std::string> archiver_split(const std::string &s, char delimiter);

#endif //ARCHIVER_H