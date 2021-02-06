#include <string>
using namespace std;

#pragma once
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

