cmake_minimum_required(VERSION 3.5)

project(own_redis)

include_directories(include)
add_library(log src/log.c)
link_libraries(log)

add_executable(client src/client.c)
add_executable(server src/server.c)