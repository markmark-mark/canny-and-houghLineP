cmake_minimum_required(VERSION 3.16)
project(bianhuan)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_BUILD_TYPE "Release")
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(bianhuan
        bianhuan.cpp)


target_link_libraries(bianhuan ${OpenCV_LIBS})