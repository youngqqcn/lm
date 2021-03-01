#ifndef LMFILESEND_H
#define LMFILESEND_H

#include "LM.h"

#define LM_FILE_TYPE_REG 0
#define LM_FILE_TYPE_DIR 1
#define LM_FILE_TYPE_LNK 2
#define LM_FILE_TYPE_OTH 3

/*
 * 封装传输一个文件或者目录的类
 * 它运行在一个单独的进程中
 * */
class LMFileSend
{
public:
    LMFileSend(int newfd, uint32_t ip);

    // 在父进程中，表示该进程id
    // 在子进程中，是0
    pid_t _pid;

    // 处理发送，是发送进程入口函数
    void process_send(int newfd, uint32_t ip);

    // 发送文件或者目录
    void send_file(char* path);

    // 修改进程的当前目录，重新获得文件的相对路径
    char* change_cwd(char* path);

    // 获得文件类型
    int file_type(char* path);

    // 获取文件长度
    uint64_t file_size(char* path);

    // 发送普通文件
    void send_reg(char* path, FILE* fp);

    // 发送目录
    void send_dir(char* path, FILE* fp);

    // 传输用的socket
    int _fd;
};

#endif // LMFILESEND_H
