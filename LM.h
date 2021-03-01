/*==================================
*   Copyright (C) 2016 All rights reserved.
*   
*   文件名称：LM.h
*   创 建 者：薛国良
*   创建日期：2016年11月11日
*   描    述：
*
================================================================*/
#ifndef _LM_H
#define _LM_H


#include <sys/time.h>
#include <unistd.h>
#include <sys/times.h>
#include <utime.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <inttypes.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <regex.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/epoll.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>

#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;
// save global data

#define LM_PORT_UDP 23250
#define LM_PORT_TCP 23251

#define LM_CMD "cmd"
#define LM_ONLINE "online"
#define LM_ONLINEACK "onlineack"
#define LM_NAME "name"
#define LM_LIST "list"
#define LM_SEND "send"
#define LM_SENDF "sendf"
#define LM_MSG "msg"
#define LM_PATH "path"
#define LM_DIR "d"
#define LM_REG "r"
#define LM_SPERATOR "5h5h"
#define LM_FILEEOF "0"

#endif //LM_H
