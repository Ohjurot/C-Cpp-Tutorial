#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef void(*ini_callback)(const char* section, const char* key, const char* value);

void ini_parseIniFromFile(const char* filePath, const char* logfilePath, ini_callback callback);
void ini_parseIni(const char* iniData, const char* logfilePath, ini_callback callback);
void ini_appendBuffer(char* buffer, char c);
void ini_stripeBuffer(char* buffer);
