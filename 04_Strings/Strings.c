#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void parseIni(const char* iniData);
void appendBuffer(char* buffer, char c);
void stripeBuffer(char* buffer);

int main()
{
    const char* iniContent = 
        "; last modified 1 April 2001 by John Doe\n"
        "[owner]\n"
        "   name = John Doe\n"
        "   organization = Acme Widgets Inc.\n"
        "\n"
        "[database]\n"
        "   ; use IP address in case network name resolution is not working\n"
        "   server = 192.0.2.62 \n"
        "   port = 143\n"
        "   file = \"payroll.dat\"\n";

    printf("=== RAW INI FILE ===\n%s\n", iniContent);
    printf("=== PARSED DATA ===\n");
    parseIni(iniContent);
}

void parseIni(const char* iniData)
{
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
        // Waiting for ini data
        if (state == 0)
        {
            if (*c == ';') state = 1; // Start comment
            else if (*c == '[') state = 2; // Start secion name
            else if (!(*c == ' ' || *c == '\t' || *c == '\n'))
            {
                appendBuffer(buffer, *c);
                state = 3; // State key
            }
        }
        // Reading comment
        else if (state == 1)
        {
            if (*c == '\n') state = 0; // End comment
        }
        // Section name stated
        else if (state == 2)
        {
            if (*c == ']') // End section name
            {
                memcpy(currentSecion, buffer, 256 * sizeof(char));
                *buffer = '\0';
                state = 0;
            }
            else if (*c == '\n') // Invalid section name (discrad)
            {
                *buffer = '\0';
                state = 0;
            }
            else
            {
                appendBuffer(buffer, *c);
            }
        }
        // Key stated
        else if (state == 3)
        {
            if (*c == ' ' || *c == '\t')
            {
                memcpy(currentKey, buffer, 256 * sizeof(char));
                *buffer = '\0';
                state = 4; // End key
            }
            else if (*c == '\n')
            {
                state = 0; // Invalid key value pair
            }
            else
            {
                appendBuffer(buffer, *c);
            }
        }
        // End of key
        else if (state == 4)
        {
            if (*c == '=') state = 5; // Ready for value
            else if (*c == '\n') state = 0; // Invalid key value pair
            else if (!(*c == ' ' || *c == '\t')) state = 7; // Invalid key value pair
        }
        // Ready for value
        else if (state == 5)
        {
            if (*c == '\n') state = 0; // Invalid key value pair
            else if (!(*c == ' ' || *c == '\t'))
            {
                appendBuffer(buffer, *c);
                state = 6; // Begin value
            }
        }
        // Start of value
        else if (state == 6)
        {
            if (*c == '\n')
            {
                stripeBuffer(buffer);
                memcpy(currentValue, buffer, 256 * sizeof(char));
                *buffer = '\0';
                state = 0;

                // Report out
                printf("Propertie: \"%s/%s\": \"%s\"\n", currentSecion, currentKey, currentValue);
            }
            else
            {
                appendBuffer(buffer, *c);
            }
        }
        else if (state == 7)
        {
            if (*c == '\n') state = 0;
        }
    }
}

void appendBuffer(char* buffer, char c)
{
    char* cursor;
    for (cursor = buffer; *cursor; cursor++);
    cursor[0] = c;
    cursor[1] = '\0';
}

void stripeBuffer(char* buffer)
{
    char* cursor;
    for (cursor = buffer; cursor[1] != '\0'; cursor++);
    while (*cursor == ' ' || *cursor == '\t')
    {
        *cursor = '\0';
        cursor--;
    }
}
