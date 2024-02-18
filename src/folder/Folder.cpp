#include "Folder.h"

Folder::Folder(const std::string& name,
               const std::vector<File>& files,
               const std::vector<Folder>& folders)
    : mName{name}
    , mFiles{files}
    , mFolders{folders}
{
}

std::string Folder::getName()
{
    return mName;
}

std::vector<File> Folder::getFiles()
{
    return mFiles;
}

std::vector<Folder> Folder::getFolders()
{
    return mFolders;
}
