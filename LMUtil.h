#ifndef LMUTIL_H
#define LMUTIL_H

#include "LM.h"

/*
 * 一些功能函数的封装（工具类）
 * */
class LMUtil
{
public:
    LMUtil();

    // 获取机器名
    static char* getHostname();

    // 获取本机ip地址
    static list<uint32_t> getLocalIpAddress();

    // 将整数的ip转化成字符串，并且函数是线程安全的
    static string ipaddr(uint32_t ip);

    // 判断地址是否广播地址
    static bool is_broadcast(string ip);
};

#endif // LMUTIL_H
