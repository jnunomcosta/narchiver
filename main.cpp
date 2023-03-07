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

int main(int argc, const char** argv)
{
    /* Archiver ar = Archiver("../sample", "../sample_output/file.nar");
    ar.archive(); */ //I think it works a

    Dearchiver dr = Dearchiver("../sample_output/file.nar", "../sample_output");
    dr.dearchive();

    return 0;
} 

