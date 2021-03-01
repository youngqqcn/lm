#ifndef LMJSON_H
#define LMJSON_H

#include <string>
using namespace std;
#include "cJSON.h"

// 对JSON对象的封装
// 负责对JSON的打包和解包
class LMJson
{
public:
    LMJson();
    ~LMJson();

    // 增加JSON的字段
    void add(string key, string value);
    // 把json对象打包成连续的内存
    string print();

    // 解包
    bool parse(char* buf);
    // 取得字段
    string get(string key);

private:
    // 内置的JSON对象
    cJSON* _root;

    // 避免使用该类的程序，错误进行拷贝构造
    LMJson(const LMJson&);
    LMJson& operator=(const LMJson&);
};

#endif // LMJSON_H
