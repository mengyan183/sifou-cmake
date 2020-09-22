//
// Created by xingguo on 2020/9/22.
//

#include "TestMain.h"
#include "external/googletest/include/gtest/gtest.h"

int add(int a, int b) {
    return a + b;
}

TEST(test1, c1) {
    EXPECT_EQ(3, add(1, 2));
}

GTEST_API_ int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <thread>

using namespace std;

void sayHello() {
    printf("helloWorld;\n");
}

/**
 * @return
 */
int threadDemo() {
    // 创建一个异步线程
    thread t(sayHello);
    // 阻塞等待当前异步线程执行结束
    t.join();
    return 0;
}

// 参考 https://www.cnblogs.com/tsts/p/11186660.html 编写测试用例
TEST(ThreadDemo,threadDemoFunction){
    threadDemo();
}