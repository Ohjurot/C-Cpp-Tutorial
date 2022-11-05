#pragma once

#include "INIApi.h"
#include "INIParser.h"

#include <stdlib.h>
#include <string.h>

typedef struct __inix_kv
{
    char* key;
    char* value;

    struct __inix_kv* nextKv;
} inix_kv;

typedef struct __inix_section
{
    char* name;
    struct __inix_kv* firstKv;

    struct __inix_section* nextSection;
} inix_section;

typedef struct __inix_data
{
    struct __inix_section* firstSection;
} inix_data;

// Public DOM api
INI_API inix_data* inix_new();
INI_API void inix_parseIniFromFile(inix_data* data, const char* filePath, const char* logfilePath);
INI_API void inix_parseIni(inix_data* data, const char* iniData, const char* logfilePath);
INI_API void inix_close(inix_data* data);
INI_API int inix_sectionExists(inix_data* data, const char* name);
INI_API int inix_keyExists(inix_data* data, const char* section, const char* key);
INI_API const char* inix_get(inix_data* data, const char* section, const char* key);
INI_API void inix_enumerate(inix_data* data, ini_callback callback, void* userdata);

// Internal helper function
inix_kv* inix_newKv(const char* key, const char* value);
inix_kv* inix_getKv(inix_kv* root, const char* name);
void inix_appendKv(inix_kv* root, const char* key, const char* value);
void inix_closeKv(inix_kv* kv);

inix_section* inix_newSection(const char* name);
inix_section* inix_appendSection(inix_section* root, const char* name);
inix_section* inix_getSection(inix_section* root, const char* name);
void inix_appendKvToSection(inix_section* section, const char* key, const char* value);
void inix_closeSection(inix_section* section);

inix_section* inix_ensureSection(inix_data* data, const char* name);
void inix_appendKvToData(inix_data* data, const char* section, const char* key, const char* value);
