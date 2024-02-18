#include <CommandParser.h>
#include <Folder.h>

#include <iostream>

int main(int argc, const char* argv[])
{
    /* File f1 = File("file1", 5), f2 = File("file2", 6);
    std::vector<File> files1 = {f1, f2};

    File f3 = File("file3", 5), f4 = File("file4", 6);
    std::vector<File> files2 = {f3, f4};

    File f5 = File("file5", 5), f6 = File("file6", 6);
    std::vector<File> files3 = {f5, f6};

    Folder fl1 = Folder("folder1", files1, std::vector<Folder>());
    Folder fl2 = Folder("folder2", files2, std::vector<Folder>());
    std::vector<Folder> folders = {fl1, fl2};

    Folder finalFolder("finalFolder", files3, folders);

    std::cout << "Folder Name = " << finalFolder.getName() << std::endl; */
    auto command_parsed = CommandParser::parseCommands(argc, argv);
}
