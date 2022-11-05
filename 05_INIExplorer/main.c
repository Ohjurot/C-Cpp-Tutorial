#include <INIx.h>

#include <stdio.h>
#include <string.h>

#if defined(INIEXPLORER_DEFAULT_FORMAT1) && !defined(INIEXPLORER_DEFAULT_FORMAT2)
#define INIEXPLORER_FORMAT_CALLBACK iniDataReady1
#elif defined(INIEXPLORER_DEFAULT_FORMAT2) && !defined(INIEXPLORER_DEFAULT_FORMAT1)
#define INIEXPLORER_FORMAT_CALLBACK iniDataReady2
#else
#error Please define EXACTLY one default format!
#endif

void iniDataReady1(void* userdata, const char* section, const char* key, const char* value)
{
    printf_s("[%s]\n%s = %s\n\n", section, key, value);
}

void iniDataReady2(void* userdata, const char* section, const char* key, const char* value)
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
    ini_callback callback = INIEXPLORER_FORMAT_CALLBACK;
    if (argc >= 3)
    {
        switch (*argv[2])
        {
            case '1':
                callback = iniDataReady1;
                break;
            case '2':
                callback = iniDataReady2;
                break;
            default:
                printf_s("Invalid format!");
                return -1;
        }
    }

    // Check logfile path
    const char* logfile = NULL;
    if (argc >= 4)
    {
        logfile = argv[3];
    }

    // Parse the ini file
    inix_data* iniData = inix_new(); 
    if (iniData)
    {
        inix_parseIniFromFile(iniData, "default.ini", logfile);
        inix_parseIniFromFile(iniData, argv[1], logfile);

        const char* ownerName = inix_get(iniData, "owner", "name");
        const char* ownerOrga = inix_get(iniData, "owner", "organization");
        printf_s("This application is operated by %s from %s\n", ownerName, ownerOrga);
        
        printf_s("\nClassical SAX Parsing following now...\n");
        inix_enumerate(iniData, callback, NULL);

        inix_close(iniData);
    }
}
