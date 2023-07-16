#include "Dearchiver.h"
#include <sstream>

std::vector<std::string> dearchiver_split(const std::string &s, char delimiter)
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

Dearchiver::Dearchiver(std::string archived_file, std::string dearchivedFolder)
{
    this->archived_file = archived_file;
    this->dearchived_folder = dearchivedFolder;
}

Dearchiver::~Dearchiver()
{
}

unsigned char handleTypeFlag(FILE *in)
{
    unsigned char flag = 0;
    if (fread(&flag, sizeof(unsigned char), 1, in) > 0)
    {
        return flag;
    }
    else
    {
        return 2;
    }
}

void readFile(FILE *in, std::string dearchived_folder)
{
    unsigned int name_size = 0;
    fread(&name_size, sizeof(unsigned int), 1, in);

    char* file_name = new char[name_size];
    auto hamb = fread(&file_name, sizeof(char), name_size, in);
    std::cout << hamb << std::endl;

    /* std::vector<char> file_name(name_size);
    for (int i = 0; i < name_size; i++)
    {
        char c;
        fread(&c, sizeof(char), 1, in);
        file_name.push_back(c);
    } */
    std::string fname;
    fname.append(dearchived_folder).append("/").append(file_name);
    delete[] file_name;
    FILE *out;
    if ((out = fopen(fname.c_str(), "wb")) != 0)
    {
        unsigned int fsize = 0;
        fread(&fsize, sizeof(unsigned int), 1, in);

        unsigned char byte_buffer[2048];
        size_t bytes_read = 0, total_bytes_read = 0;

        while (total_bytes_read < fsize)
        {
            size_t bytes2read;
            if (total_bytes_read + 2048 <= fsize)
            {
                bytes2read = 2048;
            }
            else
            {
                bytes2read = fsize - total_bytes_read;
            }
            bytes_read = fread(byte_buffer, 1, bytes2read, in);
            total_bytes_read += bytes_read;

            fwrite(byte_buffer, 1, bytes_read, out);
        }
    }
    else
    {
        std::cerr << "File could not be created\n";
    }
}

void readFolder(FILE *in, std::string dearchived_folder)
{
    unsigned int name_size = 0;
    fread(&name_size, sizeof(unsigned int), 1, in);

    char* folder_name = new char[name_size];
    fread(&folder_name, sizeof(char), name_size, in);


    /* std::vector<char> folder_name(name_size);
    for (int i = 0; i < name_size; i++)
    {
        char c;
        fread(&c, sizeof(char), 1, in);
        folder_name.push_back(c);
    } */

    int folder_contents = 0;
    fread(&folder_contents, sizeof(int), 1, in);

    std::string fname;
    fname.append(dearchived_folder).append("/").append(folder_name);
    delete[] folder_name;
    if (std::__fs::filesystem::create_directory(fname))
    {
        for (int i = 0; i < folder_contents; i++)
        {
            switch (handleTypeFlag(in))
            {
            case 0:
                readFile(in,fname);
                break;
            case 1:
                readFolder(in,fname);
                break;
            default:
                std::cerr << "Error in Default Case\n";
                break;
            }
        }
    }
    else
    {
        std::cerr << "Failed to create directory\n";
    }
}

void Dearchiver::dearchive()
{
    FILE *in;
    if ((in = fopen(this->archived_file.c_str(), "rb")) != 0)
    {
        unsigned char type_flag = 0;
        while((type_flag = handleTypeFlag(in)) != 2)
        {
            if(type_flag == 0)
            {
                readFile(in,this->dearchived_folder);
            }
            else
            {
                readFolder(in, this->dearchived_folder);
            }
        }

        if (fclose(in) != 0)
        {
            std::cerr << "Unable to close archive file\n";
        }
    }
    else
    {
        std::cerr << "Unable to open archive file\n";
    }

    /* std::string extension = this->archived_file;
    std::vector<std::string> res = dearchiver_split(extension, '/');
    std::string full_path;
    for (int i = 0; i < res.size()-1; i++) {
        full_path.append(res[i]).append("/");
    }
    extension = full_path;


    FILE* in, *fp;

    if ((in = fopen(this->archived_file.c_str(), "rb")) != 0) {

        int num_folders = 0;
        fread(&num_folders, 4, 1, in);

        int num_total_folders = 0;
        fread(&num_total_folders, 4, 1, in);

        for (int i = 0; i < num_folders; i++) {
            full_path = extension;

            int name_size = 0;
            fread(&name_size, 4, 1, in);

            char* folder_name = new char[name_size];
            fread(folder_name, sizeof(char), name_size, in);
            std::filesystem::create_directories(full_path.append(folder_name));

            int num_files = 0;
            fread(&num_files, 4, 1, in);

            for (int j = 0; j < num_files; j++) {

                int file_name_size = 0;
                fread(&file_name_size, 4, 1, in);

                char* file_name = new char[file_name_size];
                fread(file_name, sizeof(char), file_name_size, in);

                int file_size = 0;
                fread(&file_size, 4, 1, in);

                std::string st = full_path;

                const char* aux = st.append("\\").append(file_name).c_str();
                if ((fp = fopen(aux, "wb")) != 0) {

                    unsigned char byte_buffer[1024];
                    size_t bytes_read=0,total_bytes_read=0;

                    while (total_bytes_read < file_size) {
                        size_t bytes_a_ler;
                        if (total_bytes_read + 1024 <= file_size) {
                            bytes_a_ler = 1024;
                        }
                        else {
                            bytes_a_ler = file_size - total_bytes_read;
                        }
                        bytes_read = fread(byte_buffer, 1, bytes_a_ler, in);
                        total_bytes_read += bytes_read;

                        fwrite(byte_buffer, 1, bytes_read, fp);
                    }
                    //files_processed++;
                    fclose(fp);

                }
                delete[] file_name;
            }
            delete[] folder_name;
        }
        fclose(in);
    } */
}
