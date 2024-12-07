cmake_minimum_required(VERSION 3.28.3)

project(Compiler)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

include_directories(include/frontend include/llvm include/mips)

# 使用 file(GLOB) 来获取源文件列表
file(GLOB_RECURSE src_path
    "src/main.cpp"
    "src/mips/*.cpp"
    "src/frontend/*.cpp"
    "src/llvm/*.cpp"
)

# 设置编译类型
set(CMAKE_BUILD_TYPE Debug)

# 添加可执行文件
add_executable(Compiler ${src_path})

# set(CMAKE_BUILD_TYPE Release)