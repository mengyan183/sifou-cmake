//
// Created by xingguo on 2020/10/3.
//

#ifndef SIFOU_CMAKE_TESTPTHREADDEMO_H
#define SIFOU_CMAKE_TESTPTHREADDEMO_H


class TestPthreadDemo {

};

void *helloWorld(void *ptr);
void *addCount(void *ptr);
void *addCountWithMutex(void *ptr);
void *producerWithMutex(void *ptr);
void *consumerWithMutex(void *ptr);

#endif //SIFOU_CMAKE_TESTPTHREADDEMO_H
