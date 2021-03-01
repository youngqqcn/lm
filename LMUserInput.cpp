#include "LMUserInput.h"
#include "LMUtil.h"
#include "LMNetwork.h"
#include "LMJson.h"
LMUserInput::LMUserInput()
{

}

void LMUserInput::loop()
{
    // 获取命令，拆分命令，处理命令
    getcmd();
    splitcmd();
    handlecmd();
}

void LMUserInput::getcmd()
{
    while(1)
    {
        fgets(_buf, sizeof(_buf), stdin);
        if(strlen(_buf) > 1)
            break;
    }

    // remove \n
    _buf[strlen(_buf)-1] = 0;
}

/*
    list
    send 192.168.11.80: hello world
    senda: helloworld
*/
void LMUserInput::splitcmd()
{
    _args.clear();

    char* saveptr = NULL;
    char* first = strtok_r(this->_buf, ":", &saveptr);
    char* content = strtok_r(NULL, "\0", &saveptr);

    char* cmd=strtok_r(first, " \t", &saveptr);
    char* user = strtok_r(NULL, "\0", &saveptr);

    _args.push_back(cmd);
    if(user)
        _args.push_back(user);
    if(content)
        _args.push_back(content);

#if 0
    char* saveptr = NULL;
    char* first = strtok_r(this->_buf, " \t", &saveptr);
    _args.push_back(first);

    char* second = strtok_r(NULL, " \t", &saveptr);
    if(second)
        _args.push_back(second);
    else
        return;

    char* third = strtok_r(NULL, "\0", &saveptr);
    if(third)
        _args.push_back(third);

    return;
#endif
}

void LMUserInput::handlecmd()
{
#define BRANCH(cmd, func) if(_args[0] == cmd) func()

    BRANCH(LM_LIST, handlelist);
    BRANCH(LM_SEND, handlesend);
    BRANCH(LM_SENDF, handlesendf);

#if 0
    if(_args[0] == LM_LIST)
    {
        handlelist();
    }
    // send 192.168.11.60 hello world
    if(_args[0] == LM_SEND)
    {
        handlesend();
    }
#endif
}

void LMUserInput::handlelist()
{
    LMCore* core = LMCore::instance();

    printf("user list:\n");

    for(auto it = core->_others.begin();
        it != core->_others.end();
        ++it)
    {
        LMOther* other = it->second;
        printf("get other pointer is %p\n", other);
        const char* name = other->_name.c_str();
        string ip = LMUtil::ipaddr(other->_ip);

        printf("  %s(%s)\n", name, ip.c_str());
        // user list:
        //   xueguoliang(192.168.11.80)
        //   xueguoliang(192.168.11.79)
    }
}

void LMUserInput::handlesend()
{
    /* _args[0], [1], [2] */
    if(_args.size() < 3)
        return;

    string& ip = _args[1];
    string& msg = _args[2];

    bool b = LMUtil::is_broadcast(ip);

    LMJson json;
    json.add(LM_CMD, LM_SEND);
    json.add(LM_NAME, LMCore::instance()->_name);
    if(b)
        json.add(LM_MSG, msg + "[broadcast]");
    else
        json.add(LM_MSG, msg);

    LMNetwork::instance()->send(json.print(), inet_addr(ip.c_str()));
}

// sendf 192.168.11.80: path1
// _args[0] = sendf
// _args[1] = 192.168.11.80
// _args[2] = ../../aa/../../bb
void LMUserInput::handlesendf()
{
    if(_args.size() < 3)
    {
        printf("args error\n");
        return;
    }

    string& ip = _args[1];
    string& path = _args[2];

   // bool b = LMUtil::is_broadcast(ip);
    LMJson json;
    json.add(LM_CMD, LM_SENDF);
    json.add(LM_NAME, LMCore::instance()->_name);
    json.add(LM_PATH, path);

    LMNetwork::instance()->send(json.print(), inet_addr(ip.c_str()));
}


