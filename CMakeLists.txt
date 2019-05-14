cmake_minimum_required(VERSION 3.14)
project(SuperMarket)

set(CMAKE_CXX_STANDARD 14)

add_executable(SuperMarket main.cpp Goods.h Order.h Supermarket.h)