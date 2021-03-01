#ifndef LMFILERECV_H
#define LMFILERECV_H

#include "LM.h"

/*
 * 接受一个文件或者目录
 * 这是一个线程
 * */
class LMFileRecv
{
public:
    LMFileRecv(string peername, string path, uint32_t peerip);

    // 线程id
    pthread_t _tid;

    // 发送文件的账户名
    string _peername;
    // 发送文件的路径（相对于发送方的系统）
    string _peerpath;
    // 发送方的ip地址
    uint32_t _peerip;

    // 线程处理函数
    static void* thread_func(void* arg);

    // 线程真正的入口函数
    void run();

    // 接收文件
    void recv_file(int fd);

    // 用来接收一行数据
    char _buf[1024];
    char* get_line(FILE* fp);
};

#endif // LMFILERECV_H
