cmake_minimum_required(VERSION 3.5)
project(convert-pptx-api)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(convert-pptx-api convert-pptx.cpp crow_all.h)