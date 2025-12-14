cmake_minimum_required(VERSION 3.30)
project(c_lab_6 C)

set(CMAKE_C_STANDARD 23)

add_executable(c_lab_6 main.c
        declare_linked_list.h
        define_linked_list.h
        double_linked_list.c
        double_linked_list.h)
