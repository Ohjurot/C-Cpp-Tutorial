#include "INIParser.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    // Validate argument1 count
    if (argc < 2 || argc > 3)
    {
        printf_s("Usage: INIParser [PathToIniFile] <OPTIONAL:PathToLogFile>");
        return -1;
    }

    // Check logfile path
    const char* logfile = NULL;
    if (argc >= 3)
    {
        logfile = argv[2];
    }

    // Parse the ini file
    ini_parseIniFromFile(argv[1], logfile);
}
