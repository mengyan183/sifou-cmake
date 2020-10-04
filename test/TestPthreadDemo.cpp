//
// Created by xingguo on 2020/10/3.
//

#include "TestPthreadDemo.h"
#include "external/googletest/include/gtest/gtest.h"

#define MAX_THREAD_COUNT 5

int count = 0;
// 消费者锁
pthread_mutex_t consumer_mutex = PTHREAD_MUTEX_INITIALIZER;
//生产者锁
pthread_mutex_t producer_mutex = PTHREAD_MUTEX_INITIALIZER;
// 消费者条件变量
pthread_cond_t consumer_cond = PTHREAD_COND_INITIALIZER;
//生产者条件变量
pthread_cond_t producer_cond = PTHREAD_COND_INITIALIZER;

void *producerWithMutex(void *ptr) {
    for (int i = 0; i < 100; ++i) {
        // 加锁
        pthread_mutex_lock(&producer_mutex);
        if (count <= 9) {
            count++;
            printf("生产数据:%d\n", count);
            // 唤醒所有的消费线程
            pthread_cond_broadcast(&consumer_cond);
        } else {
            // 阻塞当前线程
            pthread_cond_wait(&producer_cond, &producer_mutex);
        }
        // 释放锁
        pthread_mutex_unlock(&producer_mutex);
    }
    return nullptr;
}

void *consumerWithMutex(void *ptr) {
    for (int i = 0; i < 100; ++i) {
        // 加锁
        pthread_mutex_lock(&consumer_mutex);
        if (count > 1) {
            printf("消费数据:%d\n", count);
            count--;
            // 唤醒所有的生产线程
            pthread_cond_broadcast(&producer_cond);
        } else {
            // 阻塞当前线程
            pthread_cond_wait(&consumer_cond, &consumer_mutex);
        }
        // 释放锁
        pthread_mutex_unlock(&consumer_mutex);
    }
    return nullptr;
}

TEST(PthreadDemo, condtion) {
    pthread_t *producers[MAX_THREAD_COUNT];
    pthread_t *consumers[MAX_THREAD_COUNT];
    for (int j = 0; j < MAX_THREAD_COUNT; j++) {
        pthread_t producer;
        pthread_create(&producer, nullptr, producerWithMutex, nullptr);
        producers[j] = &producer;
        pthread_t consumer;
        pthread_create(&consumer, nullptr, consumerWithMutex, nullptr);
        consumers[j] = &consumer;
    }
    for (int j = 0; j < MAX_THREAD_COUNT; j++) {
        pthread_join(*producers[j], nullptr);
        pthread_join(*consumers[j], nullptr);
    }

}


TEST(PthreadDemo, threadDemoFunction) {
    // 定义线程
    pthread_t pthread;
    pthread_attr_t attr;
    // 初始化属性
    int initCode = pthread_attr_init(&attr);
    printf("%d\n", initCode);
    // 设置栈大小
    size_t stack_size = 512 * 1000;
    int attr_stacksize_result = pthread_attr_setstacksize(&attr, stack_size);
    printf("%d\n", attr_stacksize_result);
    // 创建线程 , 第一个参数为线程指针,第二个参数为线程属性,当传递null时为默认属性,第三个参数为当前线程要执行的操作(方法),第四个参数为方法需要输入的参数
    int result = pthread_create(&pthread, &attr, helloWorld, (void *) "xing");
    printf("%d\n", result);
    pthread_join(pthread, nullptr);
    // 对象回收
    pthread_attr_destroy(&attr);
    // 线程退出
    pthread_exit(nullptr);
}

void *helloWorld(void *ptr) {
    // 获取当前线程
    pthread_t t = pthread_self();
    printf("线程id:%d,%s,helloWorld;\n", t, ptr);
    return nullptr;
}

int i = 0;
// 使用内部的宏定义
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

TEST(PthreadDemo, Mutex) {
    pthread_t t1;
    pthread_t t2;
//    pthread_create(&t1, nullptr, addCount, nullptr);
//    pthread_create(&t2, nullptr, addCount, nullptr);
    pthread_create(&t1, nullptr, addCountWithMutex, nullptr);
    pthread_create(&t2, nullptr, addCountWithMutex, nullptr);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
}

void *addCount(void *v) {
    printf("before:%d\n", i);
    i++;
    printf("after:%d\n", i);
    return nullptr;
}

// 通过加锁保证线程执行的顺序性
void *addCountWithMutex(void *v) {
    pthread_mutex_lock(&mutex);
    printf("mutex,before:%d\n", i);
    i++;
    printf("mutex,after:%d\n", i);
    pthread_mutex_unlock(&mutex);
    return nullptr;
}