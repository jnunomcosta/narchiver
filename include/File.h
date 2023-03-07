#define FILE_H
#ifdef FILE_H
#pragma once

#include <string>

class File
{
public:
	File(std::string, int);

	~File();

	void setName(std::string);
	void setSize(int);
	void setFullPath(std::string);
	
	std::string getName();
	std::string getFullPath();
	int getSize();

private:
	std::string name;
	std::string full_path;
	int size;
};

#endif //FILE_H