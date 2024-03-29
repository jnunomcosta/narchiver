#include <File.h>

File::File(std::string n,int s)
{
    this->name = n;
    this->size = s;
    this->full_path = "";
}

File::~File()
{
}

std::string File::getName() {
    return this->name;
}

void File::setName(std::string n) {
    this->name = n;
}

int File::getSize() {
    return this->size;
}

void File::setSize(int s) {
    this->size = s;
}

void File::setFullPath(std::string f)
{
    this->full_path = f;
    this->full_path.append("/").append(this->name);
}

std::string File::getFullPath()
{
    return this->full_path;
}