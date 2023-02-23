#include "Dearchiver.h"

std::vector<std::string> split(const std::string& s, char delimiter)
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

Dearchiver::Dearchiver(std::string archived_file)
{
    this->archived_file = archived_file;
}

Dearchiver::~Dearchiver()
{

}

//UNTESTED
void Dearchiver::dearchive()
{
    std::string extension = this->archived_file;
    std::vector<std::string> res = split(extension, '/');
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
    }
}

