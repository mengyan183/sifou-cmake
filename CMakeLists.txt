cmake_minimum_required(VERSION 3.17)
project(sifou_cmake)

set(CMAKE_CXX_STANDARD 14)
# googletest 相关配置 , 需要将https://github.com/google/googletest 下的googletest文件夹复制到当前工程中
set(GOOGLETEST_VERSION 1.10.0)
# googletest文件夹路径
add_subdirectory(./external/googletest)
include_directories(./external/googletest/include)
link_directories(./external/googletest)


include_directories(.)
add_executable(sifou_cmake
        fork_process_demo.cpp
        fork_process_demo.h
        LICENSE
        README.md )
# 相关测试文件以及 googletest文件夹
add_executable(sifou_cmake_test test/TestMain.cpp test/TestMain.h external/googletest test/TestPthreadDemo.cpp test/TestPthreadDemo.h test/BasiedLockDemo.cpp test/BasiedLockDemo.h)
# 输出依赖库 要求必须添加 自定义 "sifou_cmake_test" 以及 googletest中的 "gtest_main"
target_link_libraries(sifou_cmake_test gtest_main)

