#include "LMJson.h"
#include <stdlib.h>

LMJson::LMJson()
{
    _root = cJSON_CreateObject();
}

LMJson::~LMJson()
{
    cJSON_Delete(_root);
}

void LMJson::add(string key, string value)
{
    cJSON_AddItemToObject(_root, key.c_str(),
                          cJSON_CreateString(value.c_str()));
}

string LMJson::print()
{
    char* p = cJSON_Print(_root);
    string ret(p);
    free(p);
    return ret;
}

bool LMJson::parse(char *buf)
{
    cJSON* root = cJSON_Parse(buf);
    if(root == NULL)
        return false;
    cJSON_Delete(_root);
    _root = root;
    return true;
}

string LMJson::get(string key)
{
    string ret;

    cJSON* obj = cJSON_GetObjectItem(_root, key.c_str());
    ret = obj->valuestring;

    return ret;
}
