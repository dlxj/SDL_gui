cmake_minimum_required(VERSION 3.3)
project(TestTTF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2)
find_package(SDL2_IMAGE)
find_package(SDL2_TTF)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

set(SOURCE_FILES ../src/main.cpp)
add_executable(TestTTF ${SOURCE_FILES})
target_link_libraries(TestTTF ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})
