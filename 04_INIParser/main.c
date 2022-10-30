#include "INIParser.h"

#include <stdio.h>
#include <string.h>

void iniDataReady1(const char* section, const char* key, const char* value)
{
    printf_s("[%s]\n%s = %s\n\n", section, key, value);
}

void iniDataReady2(const char* section, const char* key, const char* value)
{
    printf_s("%s\\%s is %s\n", section, key, value);
}

int main(int argc, char** argv)
{
    // Validate argument count
    if (argc < 2 || argc > 4)
    {
        printf_s("Usage: INIParser [PathToIniFile] <OPTIONAL:Format(1/2)> <OPTIONAL:PathToLogFile>");
        return -1;
    }

    // Check the format
    ini_callback callback = iniDataReady1;
    if (argc >= 3 && strcmp(argv[2], "2") == 0)
    {
        callback = iniDataReady2;
    }

    // Check logfile path
    const char* logfile = NULL;
    if (argc >= 4)
    {
        logfile = argv[3];
    }

    // Parse the ini file
    ini_parseIniFromFile(argv[1], logfile, callback);
}
