#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <map>
#include <sstream>
#include <thread>
#include "File.h"
namespace fs = std::filesystem;

int total_file_number = 0, files_processed=0;

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

int func(std::map<std::string, std::vector<File>>& f,fs::path d) {
    int num_files = 0;
    for (const auto& entry : fs::directory_iterator(d)) {
        if (fs::is_directory(entry.path())) {
            num_files += func(f,entry.path());
        }
        else {
            std::vector<std::string> s234 = split(entry.path().generic_string(),'/');
            std::string folder_path, file_name;

            for (int i = 0; i < s234.size() - 1; i++) {
                if (i + 1 != s234.size() - 1) {
                    folder_path.append(s234[i]).append("\\");
                }
                else {
                    folder_path.append(s234[i]);
                }
            }

            file_name = s234[s234.size() - 1];

            File new_file = File(file_name, fs::file_size(entry.path()));
            num_files++;

            if (f.find(folder_path) != f.end()) {
                f[folder_path].push_back(new_file);
            }
            else {
                f[folder_path] = std::vector<File>();
                f[folder_path].push_back(new_file);
            }
        }
    }
    return num_files;
}

void compressor(const char* target_file, std::map<std::string, std::vector<File>>& files) {
    FILE* out, * fp;
    errno_t err, err2;
    if ((err = fopen_s(&out, target_file, "wb")) == 0) {

        int num_pastas = files.size();
        fwrite(&num_pastas, sizeof(int), 1, out);

        int num_total_files = total_file_number;
        fwrite(&num_total_files, sizeof(int), 1, out);

        for (map<std::string, std::vector<File>>::iterator it = files.begin(); it != files.end(); it++) {

            std::string st = it->first;
            const char* nome_pasta = st.c_str();
            int tamanho_nome_pasta = strlen(nome_pasta) + 1;
            int num_ficheiros = it->second.size();

            fwrite(&tamanho_nome_pasta, 4, 1, out);
            fwrite(nome_pasta, sizeof(char), tamanho_nome_pasta, out);
            fwrite(&num_ficheiros, 4, 1, out);

            for (int i = 0; i < it->second.size(); i++) {

                std::string stf = it->second[i].getName();
                const char* file_name = stf.c_str();
                int size_file_name = strlen(file_name) + 1;
                int file_size = it->second[i].getSize();

                fwrite(&size_file_name, 4, 1, out);
                fwrite(file_name, sizeof(char), size_file_name, out);
                fwrite(&file_size, 4, 1, out);

                const char* aux = st.append("\\").append(it->second[i].getName()).c_str();

                if ((err2 = fopen_s(&fp, aux, "rb")) == 0) {

                    unsigned char byte_buffer[1024];
                    size_t bytes_read;

                    while ((bytes_read = fread(byte_buffer, 1, 1024, fp)) != 0) {
                        fwrite(byte_buffer, 1, bytes_read, out);
                    }

                    files_processed++;
                    fclose(fp);
                }

                st = it->first;
            }

        }

        fclose(out);
    }
}

void decompressor(const char* compressed_file) {

    std::string extension = compressed_file;
    vector<std::string> res = split(extension, '\\');
    std::string full_path;
    for (int i = 0; i < res.size()-1; i++) {
        full_path.append(res[i]).append("\\");
    }
    extension = full_path;


    FILE* in, *fp;
    errno_t err, err2;

    if ((err = fopen_s(&in, compressed_file, "rb")) == 0) {

        int num_folders = 0;
        fread(&num_folders, 4, 1, in);

        int num_total_folders = 0;
        fread(&num_total_folders, 4, 1, in);
        total_file_number = num_total_folders;

        for (int i = 0; i < num_folders; i++) {
            full_path = extension;

            int name_size = 0;
            fread(&name_size, 4, 1, in);

            char* folder_name = new char[name_size];
            fread(folder_name, sizeof(char), name_size, in);
            fs::create_directories(full_path.append(folder_name));

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
                if ((err2 = fopen_s(&fp, aux, "wb")) == 0) {

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
                    files_processed++;
                    fclose(fp);
                    
                }
                delete[] file_name;
            }
            delete[] folder_name;
        }
        fclose(in);
    }

}

void progress(){
    while (total_file_number == 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    float files_read = (float) files_processed/total_file_number;
    while (files_read < 1.0) {
        int barWidth = 70;

        std::cout << "[";
        int pos = barWidth * files_read;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(files_read * 100.0) << " %\r";
        std::cout.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        files_read = (float) files_processed / total_file_number;
    }
}

void help() {
    printf("Welcome to Nuno's Zipper!\n");
    printf("\n\n");
    printf("");
}

int main(int argc, char* argv[])
{
    /*
    if (argc == 1) {
        help();
        return 1;
    }
    else {

    }*/

    fs::current_path("C:\\Users\\jnuno\\Downloads\\");
    
    std::map<std::string, std::vector<File>> files;

    total_file_number = func(files,"LI4-master");

    std::thread first(progress);

    //compressor("E:\\zipped_li4", files);

    //decompressor("E:\\zipped_li4");

    first.join();

    //getchar();

    //

    /*
        Esboco inicial:

        num_pastas 

        para cada pasta:
            tamanho_do_nome
            nome_dela
            numero de ficheiros

            para cada ficheiro:
                tamanho do nome
                nome
                tamanho da informacao
                bytes com a informacao
    */


    

}
