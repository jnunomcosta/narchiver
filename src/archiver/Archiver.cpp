#include "Archiver.h"
#include <sstream>

Archiver::Archiver(std::string folder_path, std::string archive_path)
{
    this->folder_path = folder_path;
    this->archive_path = archive_path;
    this->total_files = 0;
    this->files_processed = 0;
}

Archiver::~Archiver()
{
}

void writeFileByteData(FILE *arch_file_pointer, File *file)
{
    unsigned char file_flag = 0;
    fwrite(&file_flag, sizeof(unsigned char), 1, arch_file_pointer); // Flag indicating File or Folder

    auto file_name = file->getName();
    auto file_name_str = file_name.c_str();
    unsigned int file_name_size = static_cast<unsigned int>(strlen(file_name_str)) + 1;
    fwrite(&file_name_size, sizeof(unsigned int), 1, arch_file_pointer);    // Size of the File Name
    fwrite(file_name_str, sizeof(char), file_name_size, arch_file_pointer); // File Name itself

    auto file_size = file->getSize();
    fwrite(&file_size, sizeof(int), 1, arch_file_pointer); // File size
    FILE *fp;
    if ((fp = fopen(file->getFullPath().c_str(), "rb")) != NULL)
    {
        unsigned char byte_buffer[2048];
        size_t bytes_read;

        while ((bytes_read = fread(byte_buffer, 1, 2048, fp)) != 0)
        {
            fwrite(byte_buffer, 1, bytes_read, arch_file_pointer); // Writing 2048 bytes to file
        }
        fclose(fp);
    }
    else
    {
        std::cerr << "Unable to open file in binary mode to read\n";
    }
}

void writeFolderByteData(FILE *arch_file_pointer, Folder *folder, std::string folder_path)
{
    unsigned char folder_flag = 1;
    fwrite(&folder_flag, sizeof(unsigned char), 1, arch_file_pointer); // Flag indicating File or Folder

    auto folder_name = folder->getName();
    auto folder_name_str = folder_name.c_str();
    unsigned int folder_name_size = static_cast<unsigned int>(strlen(folder_name_str)) + 1;
    fwrite(&folder_name_size, sizeof(unsigned int), 1, arch_file_pointer);           // Size of the Folder Name
    fwrite(folder_name_str, sizeof(char), folder_name_size, arch_file_pointer); // Folder Name itself

    auto folder_contents = folder->getContents();
    fwrite(&folder_contents, sizeof(int), 1, arch_file_pointer); // Contents

    for (auto subfile : folder->getFiles())
    {
        subfile->setFullPath(folder_path);
        writeFileByteData(arch_file_pointer, subfile);
    }

    for (auto subfolder : folder->getFolders())
    {
        writeFolderByteData(arch_file_pointer, subfolder, folder_path.append("/").append(subfolder->getName()));
    }
}

void Archiver::archive()
{
    this->folder_archive = new Folder("");

    total_files = loadFiles(this->folder_path, this->folder_path, this->folder_archive);

    FILE *out;
    if ((out = fopen(archive_path.c_str(), "wb")) != NULL)
    {
        for (auto file : this->folder_archive->getFiles())
        {
            file->setFullPath(folder_path);
            writeFileByteData(out,file);
        }

        for (auto folder : this->folder_archive->getFolders())
        {
            std::string current_folder_path = folder_path;
            current_folder_path.append("/").append(folder->getName());
            writeFolderByteData(out,folder,current_folder_path);
        }

        if(fclose(out) != 0)
        {
            std::cerr << "Failed to close archive file." << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to open archive file for writing." << std::endl;
        delete this->folder_archive;
        return;
    }

    delete this->folder_archive;

    /* FILE* out, * fp;

    if ((out = fopen(archive_path.c_str(), "wb")) != NULL) {

        int folder_number = files.size();
        fwrite(&folder_number, sizeof(int), 1, out);

        fwrite(&total_files, sizeof(int), 1, out);

        for (std::map<std::string, std::vector<File>>::iterator it = files.begin(); it != files.end(); it++)
        {

            std::string st = it->first;
            const char* folder_name = st.c_str();
            int folder_name_size = strlen(folder_name) + 1;
            int file_num = it->second.size();

            fwrite(&folder_name_size, sizeof(int), 1, out);
            fwrite(folder_name, sizeof(char), folder_name_size, out);
            fwrite(&file_num, sizeof(int), 1, out);

            for (int i = 0; i < it->second.size(); i++) {

                std::string stf = it->second[i].getName();
                const char* file_name = stf.c_str();
                int size_file_name = strlen(file_name) + 1;
                int file_size = it->second[i].getSize();

                fwrite(&size_file_name, sizeof(int), 1, out);
                fwrite(file_name, sizeof(char), size_file_name, out);
                fwrite(&file_size, sizeof(int), 1, out);

                auto file_path = st.append("/").append(it->second[i].getName()).c_str();

                if ((fp = fopen(file_path, "rb")) != NULL) {

                    unsigned char byte_buffer[1024];
                    size_t bytes_read;

                    while ((bytes_read = fread(byte_buffer, 1, 1024, fp)) != 0) {
                        fwrite(byte_buffer, 1, bytes_read, out);
                    }

                    this->files_processed++;
                    fclose(fp);
                }

                st = it->first;
            }

        }

        fclose(out);
    } */
}

std::vector<std::string> archiver_split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int loadFiles(std::string base_path, std::string current_path, Folder *base_folder)
{
    int num_files = 0;

    for (const auto &entry : std::__fs::filesystem::directory_iterator(current_path))
    {
        if (std::__fs::filesystem::is_directory(entry))
        {
            /* std::cout << "Filename => " << entry.path().filename() << " - ";                           // ex: folder2
            std::cout << "Relative => " << std::filesystem::relative(entry.path(), base_path) << "\n"; // ex: folder1/folder2 */
            Folder *fol = new Folder(entry.path().filename());
            base_folder->addFolder(fol);
            loadFiles(base_path, entry.path(), fol);
        }
        else
        {
            /* std::cout << "Filename => " << entry.path().filename() << " - ";                           // ex: file3.txt
            std::cout << "Relative => " << std::filesystem::relative(entry.path(), base_path) << "\n"; // ex: folder1/folder2/file3.txt */
            base_folder->addFile(new File(entry.path().filename(), std::__fs::filesystem::file_size(entry.path())));
        }
    }

    return num_files;
}

int Archiver::getfiles(std::string folderPath)
{
    int num_files = 0;
    // std::shared_ptr<Folder> current_folder = this->folder_archive;
    for (const auto &entry : std::__fs::filesystem::directory_iterator(folderPath))
    {
        // auto a = std::filesystem::relative(entry.path(), folder_path);// << std::endl;
        // std::cout << std::filesystem::relative(entry.path(), folder_path) << std::endl;
        // std::cout << entry.path() << std::endl;

        if (std::__fs::filesystem::is_directory(entry))
        {
            /* std::cout << entry.path().filename() << "\n";
            std::cout << "Relative => " << std::filesystem::relative(entry.path(), folder_path) << "\n"; */
            getfiles(entry.path());
            // current_folder->addFolder(std::make_shared<Folder>(new Folder(entry.path().filename())));
        }
        else
        {
            std::cout << entry.path().filename() << "\n";
        }

        // TODO

        //    ---> Make the process relative and not relying on the entire path

        /* if (std::filesystem::is_directory(entry.path()))
        {
            num_files += getfiles(entry.path());
        }
        else
        {
            std::vector<std::string> s234 = archiver_split(entry.path().generic_string(),'/');
            std::string folder_path, file_name;

            for (int i = 0; i < s234.size() - 1; i++)
            {
                if (i + 1 != s234.size() - 1)
                {
                    folder_path.append(s234[i]).append("/");
                }
                else
                {
                    folder_path.append(s234[i]);
                }
            }

            file_name = s234[s234.size() - 1];

            File new_file = File(file_name, std::filesystem::file_size(entry.path()));
            num_files++;

            if (files.find(folder_path) != files.end())
            {
                files[folder_path].push_back(new_file);
            }
            else
            {
                files[folder_path] = std::vector<File>();
                files[folder_path].push_back(new_file);
            }
        } */
    }
    return num_files;
}
