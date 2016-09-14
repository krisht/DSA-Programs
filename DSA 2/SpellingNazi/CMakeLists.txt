cmake_minimum_required(VERSION 3.0)
project(SpellingNazi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SpellingNazi.cpp SpellingNazi.h HashTable.cpp HashTable.h)
add_executable(SpellingNazi ${SOURCE_FILES})