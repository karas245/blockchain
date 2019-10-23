cmake_minimum_required(VERSION 3.13)
project(blockchain)

set(CMAKE_CXX_STANDARD 14)

add_executable(blockchain main.cpp header.h block.cpp block.h fun.cpp picosha2.h Blockchain.h)