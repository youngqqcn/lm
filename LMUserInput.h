#ifndef LMUSERINPUT_H
#define LMUSERINPUT_H

#include "LMCore.h"

/*
 * 用户收入处理类
 * */
class LMUserInput
{
public:
    LMUserInput();

    // 用户输入缓冲
    char _buf[4096];
    // 将用户输入拆分结果
    // send 192.168.11.80:hello world
    // senda: 1912312
    // sendf 192.168.11.80: a.txt
    vector<string> _args;

    // 一次循环处理
    void loop();

private:
    // 获取命令到_buf
    void getcmd();
    // 将_buf拆分到_args
    void splitcmd();
    // 处理命令（总入口）
    void handlecmd();

    void handlelist();
    void handlesend();
    void handlesendf();
};

#endif // LMUSERINPUT_H
