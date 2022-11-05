#pragma once

#include "INIApi.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef void(*ini_callback)(void* userdata, const char* section, const char* key, const char* value);

// SAX Api
void INI_API ini_parseIniFromFile(const char* filePath, const char* logfilePath, ini_callback callback, void* userdata);
void INI_API ini_parseIni(const char* iniData, const char* logfilePath, ini_callback callback, void* userdata);
void ini_appendBuffer(char* buffer, char c);
void ini_stripeBuffer(char* buffer);
