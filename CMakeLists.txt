cmake_minimum_required(VERSION 3.3)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
include_directories(${CMAKE_SOURCE_DIR}/src/rapidjson)

set(SOURCE_FILES src/server/main.cpp
        src/server/base_server.cpp
        src/server/base_server.hpp
        src/server/threaded_server.cpp
        src/server/threaded_server.hpp
        src/server/user.cpp
        src/server/user.hpp src/server/api.cpp src/server/api.hpp)
add_executable(server ${SOURCE_FILES})