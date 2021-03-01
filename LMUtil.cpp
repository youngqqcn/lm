#include "LMUtil.h"
#include <string.h>
LMUtil::LMUtil()
{

}

char *LMUtil::getHostname()
{
    static char hostname[128] = {0};
    if(strlen(hostname) != 0)
        return hostname;

    FILE* fp = fopen("/etc/hostname", "r");
    fgets(hostname, sizeof(hostname), fp);
    hostname[strlen(hostname)-1] = 0;
    fclose(fp);

    return hostname;
}

list<uint32_t> LMUtil::getLocalIpAddress()
{
    list<uint32_t> ret;
    FILE* fp = popen("ifconfig  | grep inet | grep -v inet6 | awk '{print $2}' | awk -F \":\" '{print $2}'", "r");

    char buf[128];
    while(fgets(buf, sizeof(buf), fp))
    {
        buf[strlen(buf)-1] = 0;
        uint32_t ip = inet_addr(buf);
        ret.push_back(ip);
    }

    pclose(fp);
    return ret;
}

string LMUtil::ipaddr(uint32_t ip)
{
    uint8_t* p = (uint8_t*)&ip;
    char buf[128];
    sprintf(buf, "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return string(buf);
}

bool LMUtil::is_broadcast(string ip)
{
    const char* p = ip.c_str();
    const char* pos = rindex(p, '.');
    pos ++;
    if(strcmp(pos, "255") == 0)
        return true;
    return false;

}
