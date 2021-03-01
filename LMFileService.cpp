#include "LMFileService.h"
#include "LMFileSend.h"

LMFileService::LMFileService()
{

}

LMFileService *LMFileService::instance()
{
    static LMFileService* o = NULL;
    if(o) return o;
    return o = new LMFileService;
}

void LMFileService::start()
{
    _pid = fork();
    if(_pid == 0)
    {
        sub_process_run();
        exit(0);
    }
}

void LMFileService::sub_process_run()
{
    signal(SIGCHLD, child_process_end);

    _listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(LM_PORT_TCP);
    addr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(_listenfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        printf("file trans services bind error\n");
        exit(1);
    }

    listen(_listenfd, 20);

    socklen_t len=sizeof(addr);

    while(1)
    {
        int newfd = accept(_listenfd, (struct sockaddr*)&addr, &len);

        if(_bChildProcessEnd)
        {
            while(1)
            {
                int status;
                pid_t pid = waitpid(-1, &status, WNOHANG);
                if(pid <= 0)
                    break;

                // status
                if(WIFEXITED(status))
                {
                    LMFileSend* s = _fileSendingProcess[pid];
                    delete s;
                    _fileSendingProcess.erase(pid);

                    // error
                    if(WEXITSTATUS(status) != 0)
                    {
                        printf("file trans error, code=%d", WEXITSTATUS(status));
                    }
                }
            }
            _bChildProcessEnd = false;
        }

        // ping bi xinhao
        LMFileSend* s = new LMFileSend(newfd, addr.sin_addr.s_addr);
        _fileSendingProcess[s->_pid] = s;
        close(newfd);
    }
}

void LMFileService::child_process_end(int sig)
{
    instance()->_bChildProcessEnd = true;
}
