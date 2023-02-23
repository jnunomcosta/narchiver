#include "Archiver.h"

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

void Archiver::archive()
{
    total_files = getfiles(this->folder_path);

    FILE* out, * fp;
    
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
    }

}

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

int Archiver::getfiles(std::string folder_path)
{
    int num_files = 0;
    // TODO: recursive_directory_iterator is also an option
    for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
        
        /* TODO
            std::cout << std::filesystem::relative(entry.path(), folderPath) << std::endl; 
            ---> Make the process relative and not relying on the entire path
        */
        if (std::filesystem::is_directory(entry.path())) 
        {
            num_files += getfiles(entry.path());
        }
        else 
        {
            std::vector<std::string> s234 = split(entry.path().generic_string(),'/');
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
        }
    }
    return num_files;
}
