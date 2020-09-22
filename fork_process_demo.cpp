//
// Created by xingguo on 2020/9/22.
//

#include "fork_process_demo.h"
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstdio>
#include <sys/wait.h>
#include <cstdlib>
#include <cerrno>

int main() {
    pid_t childPID;

    for (int i = 0; i < 3; ++i) {
        childPID = fork();
        if (childPID==-1){
            perror("创建子进程失败");
            continue;
        } else if (childPID==0){
            printf("子进程创建成功,当前代码为子进程执行;进程号为:%d\n",getpid());
        } else{
            printf("当前代码为主进程执行;进程号为:%d\n",getpid());
        }
    }
    return 0;
}
