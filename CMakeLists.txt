cmake_minimum_required(VERSION 3.16)
project(fizkat)

set(CMAKE_CXX_STANDARD 20)

add_executable(fizkat
        main.cpp
        Fleet.cpp
        Inventory.cpp
        ServiceCenter.cpp
        Things.cpp
        Transport.cpp
)

target_compile_options(fizkat PRIVATE -Wall -Wextra)