#include "File.h"

File::File(const std::string& name, const uint64_t size)
    : mName{name}
    , mSize{size}
{
}

std::string File::getName()
{
    return mName;
}

uint64_t File::getSize()
{
    return mSize;
}
