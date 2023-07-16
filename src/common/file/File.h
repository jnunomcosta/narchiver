#define FILE_H
#ifdef FILE_H
#pragma once

#include <string>

class File
{
public:
	File(std::string, uint64_t);

	~File();

	void setName(std::string);
	void setSize(uint64_t);
	void setFullPath(std::string);
	
	std::string getName();
	std::string getFullPath();
	uint64_t getSize();

private:
	std::string name;
	std::string full_path;
	uint64_t size;
};

#endif //FILE_H