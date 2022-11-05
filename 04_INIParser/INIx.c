#include "INIx.h"

void inix_parseIniFromFile(inix_data* data, const char* filePath, const char* logfilePath)
{
    ini_parseIniFromFile(filePath, logfilePath, inix_appendKvToData, data);
}

void inix_parseIni(inix_data* data, const char* iniData, const char* logfilePath)
{
    ini_parseIni(iniData, logfilePath, inix_appendKvToData, data);
}

void inix_close(inix_data* data)
{
    if (data)
    {
        if (data->firstSection)
        {
            inix_closeSection(data->firstSection);
        }
        free(data);
    }
}

int inix_sectionExists(inix_data* data, const char* name)
{
    return data->firstSection && inix_getSection(data->firstSection, name);
}

int inix_keyExists(inix_data* data, const char* section, const char* key)
{
    if (data->firstSection)
    {
        inix_section* s = inix_getSection(data->firstSection, section);
        if (s)
        {
            if (s->firstKv)
            {
                return 1 && inix_getKv(s->firstKv, key);
            }
        }
    }

    return 0;
}

const char* inix_get(inix_data* data, const char* section, const char* key)
{
    if (data->firstSection)
    {
        inix_section* s = inix_getSection(data->firstSection, section);
        if (s && s->firstKv)
        {
            inix_kv* kv = inix_getKv(s->firstKv, key);
            if (kv)
            {
                return kv->value;
            }
        }
    }

    return NULL;
}

void inix_enumerate(inix_data* data, ini_callback callback, void* userdata)
{
    for (inix_section* section = data->firstSection; section; section = section->nextSection)
    {
        for (inix_kv* kv = section->firstKv; kv; kv = kv->nextKv)
        {
            callback(userdata, section->name, kv->key, kv->value);
        }
    }
}

inix_data* inix_new()
{
    inix_data* data = malloc(sizeof(inix_data));
    if (data)
    {
        data->firstSection = NULL;
    }
    return data;
}

inix_kv* inix_newKv(const char* key, const char* value)
{
    inix_kv* kv = malloc(sizeof(inix_kv));
    if (kv)
    {
        kv->key = _strdup(key);
        kv->value = _strdup(value);
        kv->nextKv = NULL;
    }
    return kv;
}

inix_kv* inix_getKv(inix_kv* root, const char* name)
{
    if (strcmp(root->key, name) == 0)
    {
        return root;
    }
    if (root->nextKv)
    {
        return inix_getKv(root->nextKv, name);
    }
    return NULL;
}

void inix_appendKv(inix_kv* root, const char* key, const char* value)
{
    while (root->nextKv)
    {
        root = root->nextKv;
    }

    root->nextKv = inix_newKv(key, value);
}

void inix_closeKv(inix_kv* kv)
{
    if (kv->nextKv)
    {
        inix_closeKv(kv->nextKv);
    }

    if(kv->key) free(kv->key);
    if(kv->value) free(kv->value);
    free(kv);
}

inix_section* inix_newSection(const char* name)
{
    inix_section* section = malloc(sizeof(inix_section));
    if (section)
    {
        section->name = _strdup(name);
        section->firstKv = NULL;
        section->nextSection = NULL;
    }
    return section;
}

inix_section* inix_appendSection(inix_section* root, const char* name)
{
    while (root->nextSection)
    {
        root = root->nextSection;
    }

    root->nextSection = inix_newSection(name);
    return root->nextSection;
}

inix_section* inix_getSection(inix_section* root, const char* name)
{
    inix_section* foundSection = NULL;
    for (inix_section* section = root; section; section = section->nextSection)
    {
        if (strcmp(section->name, name) == 0)
        {
            foundSection = section;
            break;
        }
    }
    return foundSection;
}

void inix_appendKvToSection(inix_section* section, const char* key, const char* value)
{
    if (section->firstKv)
    {
        inix_appendKv(section->firstKv, key, value);
    }
    else
    {
        section->firstKv = inix_newKv(key, value);
    }
}

void inix_closeSection(inix_section* section)
{
    if (section->nextSection)
    {
        inix_closeSection(section->nextSection);
    }
    if (section->firstKv)
    {
        inix_closeKv(section->firstKv);
    }

    if (section->name) free(section->name);
    free(section);
}

inix_section* inix_ensureSection(inix_data* data, const char* name)
{
    // Check if section exists
    inix_section* foundSection = NULL;
    if (data->firstSection)
    {
        foundSection = inix_getSection(data->firstSection, name);
    }

    // Insert section if it is not exsisting
    if (!foundSection)
    {
        if (data->firstSection)
        {
            foundSection = inix_appendSection(data->firstSection, name);
        }
        else
        {
            foundSection = data->firstSection = inix_newSection(name);
        }
    }

    return foundSection;
}

void inix_appendKvToData(inix_data* data, const char* section, const char* key, const char* value)
{
    inix_section* s = inix_ensureSection(data, section);
    if (s)
    {
        if (s->firstKv)
        {
            inix_kv* kv = inix_getKv(s->firstKv, key);
            if (kv)
            {
                if(kv->value) free(kv->value);
                kv->value = _strdup(value);
            }
            else
            {
                inix_appendKv(s->firstKv, key, value);
            }
        }
        else
        {
            s->firstKv = inix_newKv(key, value);
        }
    }
}
