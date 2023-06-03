cmake_minimum_required(VERSION 3.25)
project(Linked_List_Demo)

set(CMAKE_CXX_STANDARD 23)

add_executable(Linked_List_Demo main.cpp lists.h)

target_link_libraries(Linked_List_Demo -static-libstdc++)