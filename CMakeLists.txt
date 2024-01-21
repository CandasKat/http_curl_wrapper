cmake_minimum_required(VERSION 3.27)
project(http_curl_wrapper)

set(CMAKE_CXX_STANDARD 23)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_subdirectory(lib/googletest)
add_subdirectory(lib/json-develop)
add_subdirectory(src)
add_subdirectory(tst)