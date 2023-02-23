/*
CURRENT STRUCTURE:
    - Number of Folders
        -- For each folder:
            - Name size
            - Name in bytes
            - Number of files
                -- For each file:
                    - Name size
                    - Name in bytes
                    - Size
                    - Bytes
*/

#include <Archiver.h>
#include <Dearchiver.h>

int main(int argc, char** argv)
{
    for(int i=0;i<argc;i++)
    {
        std::cout << argv[i] << "\n";
    }

    FILE* aaaa = fopen("helo2.ar","w");
    fprintf(aaaa,"olaolaoa%d\n",69);
    fclose(aaaa);

    Archiver ar = Archiver("path/to/folder", "path/to/archive/helo.nar");
    ar.archive();

    Dearchiver dr = Dearchiver("path/to/archive/helo.nar");
    dr.dearchive();

    return 0;
} 

