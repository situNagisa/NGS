cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")
set(CMAKE_EXE_LINKER_FLAGS "-static")

project(NAGISA CXX)

set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

add_executable(NGS 
	src/main.cpp
)

target_include_directories(NGS PRIVATE ${PROJECT_INCLUDE_DIR})

add_subdirectory(include)