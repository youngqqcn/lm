
#include "LMUserInput.h"
#include "LMNetwork.h"
#include "LMJson.h"
#include "LMUtil.h"
#include "LMFileService.h"

int main(int argc, char* argv[])
{
    // 创建文件传输服务进程
    LMFileService::instance()->start();

    /* 创建网络数据接收线程 */
    LMNetwork* network = LMNetwork::instance();
    
    /* 告诉局域网中的所有，我上线了 */
    LMJson json;
    json.add(LM_CMD, LM_ONLINE);
    json.add(LM_NAME, LMUtil::getHostname()); /*  read /etc/hostname */
    network->send(json.print());

    /* 主线程获取用户输入，根据用户输入处理 */
    /*
     *  list
     *  send 192.168.11.90: hello
     *  sendf 192.168.11.90:../a.out
     *  send 255.255.255.255: hello
     *  sendf 255.255.255.255:../a.out
     * */
    LMUserInput input;
    while(1)
    {
        input.loop();
    }

    return 0;
}
