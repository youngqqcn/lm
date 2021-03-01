#ifndef LMCORE_H
#define LMCORE_H

#include "LM.h"

/*
 * 记录其他账户信息
 * */
class LMOther
{
public:
    // 账户名
    string _name;
    // ip地址
    uint32_t _ip;
};

/*
 * 核心数据结构
 * */
class LMCore
{
public:
    // 本地账户名：默认机器名
    string _name;
    // 本地ip地址列表
    list<uint32_t> _ips;
    // 其他账户信息，以ip为key
    map<uint32_t, LMOther*> _others;
    // 锁，用来安全访问数据
    pthread_mutex_t _mutex;

    // 添加一个账户，当收到别人上线广播，或者我广播之后，收到别人的回应
    // 调用该函数添加账户
    void add_user(uint32_t ip, string name);

    // 单例实现
    static LMCore* instance()
    {
        static LMCore* theOne = NULL;
        if(theOne) return theOne;
        return theOne = new LMCore;
    }

private:
    // 私有构造函数，因为单例
    LMCore();
};

// 自动加锁 解锁类
class LMLock
{
public:
    LMLock();
    ~LMLock();
};

#endif // LMCORE_H
