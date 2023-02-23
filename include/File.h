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
	
	std::string getName();
	int getSize();

private:
	std::string name;
	int size;
};

#endif //FILE_H