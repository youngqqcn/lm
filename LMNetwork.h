#ifndef LMNETWORK_H
#define LMNETWORK_H

#include "LMCore.h"
#include "LM.h"
#include "LMJson.h"

/*
 * 负责从网络上收数据
 * 封装单独的线程，进行收取数据
 * */
class LMNetwork
{
public:
    // 单例封装
    static LMNetwork* instance();

    // udp socket，用来发送和接收数据
    int _udpfd;
    // 线程id
    pthread_t _tid;
    // 网络数据缓冲
    char _buf[4096];

    // 线程入口函数
    // 上下文 context
    static void* thread_func(void* ptr);
    void* _thread_func(void*);

    // 发送接口函数
    void send(string msg, uint32_t ip=0xffffffff);

private:
    // 收到数据之后的处理函数
    void handle_online_ack(LMJson& json, uint32_t peerip);
    void handle_online(LMJson& json, uint32_t peerip);
    void handle_send_msg(LMJson& json);
    void handle_send_file(LMJson& json, uint32_t peerip);

private:
    LMNetwork();
};

#endif // LMNETWORK_H
