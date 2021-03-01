#ifndef LMFILESERVICE_H
#define LMFILESERVICE_H

#include "LM.h"
#include "LMFileSend.h"
/*
 * 文件传输服务器进程
 * */
class LMFileService
{
public:
    static LMFileService* instance();

    // 进程的pid，在父进程中，该值是文件传输进程pid
    // 在本进程中，是0
    pid_t _pid;

    // 监听socket
    int _listenfd;

    // 创建进程
    void start();

    // 服务器进程入口函数
    void sub_process_run();

    // 传输进程的结束信号处理函数
    static void child_process_end(int sig);

    // 文件传输进程的记录
    map<pid_t, LMFileSend*> _fileSendingProcess;

    // 为了避免信号处理函数和主进程竞争，引入的状态量
    // 表示当前有一些子进程结束
    bool _bChildProcessEnd;

private:
    LMFileService();
};

#endif // LMFILESERVICE_H
