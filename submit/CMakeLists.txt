cmake_minimum_required(VERSION 3.28.3)

project(Compiler)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(include)

aux_source_directory(src src_path)

add_executable(Compiler ${src_path})