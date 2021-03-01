#include "LMCore.h"
#include "LMUtil.h"
void LMCore::add_user(uint32_t ip, string name)
{
    LMLock lock;
    LMOther* other; 

    auto it = _others.find(ip);
    if(it == _others.end())
    {
        other = new LMOther;
        other->_ip = ip;
        other->_name = name;
        _others[ip] = other;
    }
    else
    {
        _others[ip]->_name = name;
    }

    printf("add_user other is:%p\n", other);
}

LMCore::LMCore()
{
    _ips = LMUtil::getLocalIpAddress();
    _name = LMUtil::getHostname();

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&this->_mutex, &attr);
}

LMLock::LMLock()
{
    pthread_mutex_lock(&LMCore::instance()->_mutex);
}

LMLock::~LMLock()
{
    pthread_mutex_unlock(&LMCore::instance()->_mutex);
}
