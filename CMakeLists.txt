cmake_minimum_required(VERSION 3.18.4)

project(openGL VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)
#include_directories(build/_deps/openssl-src/include)

#add_subdirectory(external)
add_subdirectory(src)
