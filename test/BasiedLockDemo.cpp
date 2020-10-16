//
// Created by xingguo on 2020/10/15.
//

#include "BasiedLockDemo.h"
#include "external/googletest/include/gtest/gtest.h"

static const uintptr_t locked_value             = 0;
static const uintptr_t unlocked_value           = 1;
static const uintptr_t monitor_value            = 2;
static const uintptr_t marked_value             = 3;
static const uintptr_t biased_lock_pattern      = 5;

TEST(BasiedLockDemo, inflat) {
    bool result;
    // 对于 object header 从偏向锁到膨胀的过程
    setValue(monitor_value);
    result =  has_monitor();
    assert(result);
    printf("%lu\n",(value() & monitor_value));
}

uintptr_t sharedValue = 0;

void setValue(uintptr_t value){
    sharedValue = value;
}

uintptr_t value(){
    return sharedValue;
}

bool has_monitor()  {
    return ((value() & monitor_value) != 0);
}