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
#include <ThreadDmo.h>
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

#include <thread>

using namespace std;

void sayHello() {
    printf("helloWorld;\n");
}


/**
 * TODO 如何编写单元测试
 * @return
 */
int threadDemo() {
    // 创建一个异步线程
    thread t(sayHello);
    // 阻塞等待当前异步线程执行结束
    t.join();
    return 0;
}