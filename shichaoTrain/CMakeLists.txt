cmake_minimum_required(VERSION 3.22)
project(trainCache)

set(CMAKE_CXX_STANDARD 14)

add_executable(trainCache ticket.cpp ticket.h main.cpp matchTransform.cpp matchTransform.h Train.h User.h order.h files.cpp files.h)
