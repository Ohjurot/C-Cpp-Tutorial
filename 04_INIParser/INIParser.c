#include "INIParser.h"

void ini_parseIniFromFile(const char* filePath, const char* logfilePath, ini_callback callback)
{
    FILE* file = NULL;
    fopen_s(&file, filePath, "rb");
    if (file)
    {
        // Open file for reading
        size_t fileSize = 0;
        fseek(file, 0, SEEK_END);
        fileSize = ftell(file);
        rewind(file);
        
        char* fileContent = malloc(fileSize + 1);
        if (fileContent)
        {
            if (fread(fileContent, fileSize, 1, file) == 1)
            {
                // Read sucess
                fileContent[fileSize] = '\0';
                ini_parseIni(fileContent, logfilePath, callback);
            }
            free(fileContent);
        }

        fclose(file);
    }
}

void ini_parseIni(const char* iniData, const char* logfilePath, ini_callback callback)
{
    // Open a log file
    FILE* log = NULL;
    if (logfilePath)
    {
        fopen_s(&log, logfilePath, "wb");
    }

    // Working buffer
    char buffer[256];
    *buffer = '\0';

    // Current values
    char currentSecion[256];
    *currentSecion = '\0';
    char currentKey[256];
    char currentValue[256];

    /*
    *  0 - Ready for INI Data
    *  1 - Comment started
    *  2 - Secion Name started
    *  3 - Key started
    *  4 - Key finished
    *  5 - Ready for value
    *  6 - Value startd
    *  7 - Invalid data
    */
    int32_t state = 0;
    for (const char* c = iniData; *c; c++)
    {
        switch (state)
        {
            // Waiting for ini data
            case 0:
                switch (*c)
                {
                    case ';': // Start comment
                        state = 1; 
                        break;
                    case '[': // Start secion name
                        state = 2; 
                        break;
                    case ' ': // Valid spacings
                    case '\t':
                    case '\n':
                        break;
                    default: // State key
                        ini_appendBuffer(buffer, *c);
                        state = 3; 
                        break;
                }
                break;

            // Reading comment
            case 1:
                if (*c == '\n') state = 0; // End comment
                break;

            // Section name stated
            case 2:
                switch (*c)
                {
                    case ']': // End section name
                        strcpy_s(currentSecion, 256, buffer);
                        *buffer = '\0';
                        state = 0;
                        break;
                    case '\n': // Invalid section name (discrad)
                        *buffer = '\0';
                        state = 0;
                        break;
                    default:
                        ini_appendBuffer(buffer, *c);
                        break;
                }
                break;

            // Key stated
            case 3:
                switch (*c)
                {
                    case ' ': // End key
                    case '\t':
                        strcpy_s(currentKey, 256, buffer);
                        *buffer = '\0';
                        state = 4; 
                        break;
                    case '\n': // Invalid key value pair
                        state = 0; 
                        break;
                    default:
                        ini_appendBuffer(buffer, *c);
                        break;
                }
                break;

            // End of key
            case 4:
                switch (*c)
                {
                    case '=': // Ready for value
                        state = 5;
                        break;
                    case '\n': // Invalid key value pair
                        state = 0;
                        break;
                    case ' ':
                    case '\t':
                        break;
                    default: // Invalid key value pair
                        state = 7;
                        break;
                }
                break;

            // Ready for value
            case 5:
                switch (*c)
                {
                    case '\n': // Invalid key value pair
                        state = 0;
                        break;
                    case ' ':
                    case '\t':
                        break;
                    default: // Begin value
                        ini_appendBuffer(buffer, *c);
                        state = 6; 
                        break;
                }
                break;

            // Start of value
            case 6:
                switch (*c)
                {
                    case '\n': // End of value
                        ini_stripeBuffer(buffer);
                        strcpy_s(currentValue, 256, buffer);
                        *buffer = '\0';
                        state = 0;

                        // Report out
                        callback(currentSecion, currentKey, currentValue);
                        if (log)
                        {
                            fprintf_s(log, "Section = \"%s\" Key = \"%s\" Value = \"%s\"\n", 
                                currentSecion, currentKey, currentValue);
                        }

                        break;
                    case '\t': // Replace tab with spaces
                        strcat_s(buffer, 256, "    ");
                        break;
                    default:
                        ini_appendBuffer(buffer, *c);
                        break;
                }
                break;

            // Invalid value
            case 7:
                if (*c == '\n') state = 0;
                break;
        }
    }

    if (log)
    {
        fclose(log);
    }
}

void ini_appendBuffer(char* buffer, char c)
{
    if (!iscntrl(c))
    {
        char str[2] = { c, '\0' };
        strcat_s(buffer, 256, str);
    }
}

void ini_stripeBuffer(char* buffer)
{
    char* c = &buffer[strlen(buffer) - 1];
    if (*c == ' ' || *c == '\t')
    {
        *c = '\0';
        ini_stripeBuffer(buffer);
    }
}
