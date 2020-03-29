cmake_minimum_required(VERSION 3.13)
project(SO2_filozofowie)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} --std=c++11 -pthread")

if (CMAKE_BUILD_TYPE MATCHES "Rel")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static -lpthread")
endif (CMAKE_BUILD_TYPE MATCHES "Rel")

add_executable(SO2_filozofowie main.cpp Program.cpp Program.hpp Philosopher.cpp Philosopher.hpp Waiter.cpp Waiter.hpp WaitForInput.cpp WaitForInput.hpp)