#include <Folder.h>

Folder::Folder(std::string n)
{
    this->name = n;
    this->files = std::vector<File>();
    this->subfolders = std::vector<Folder>();
}

Folder::~Folder()
{
}

std::string Folder::getName() {
    return this->name;
}

void Folder::setName(std::string n) {
    this->name = n;
}

void Folder::addFile(File& f) {
    this->files.push_back(f);
}

void Folder::addFolder(Folder& f) {
    this->subfolders.push_back(f);
}