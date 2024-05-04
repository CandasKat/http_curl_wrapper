cmake_minimum_required(VERSION 3.22)
project(http_curl_wrapper)

set(CMAKE_CXX_STANDARD 20)
if(MSVC)
  add_compile_options(/fsanitize=address)
  add_link_options(/INCREMENTAL:NO /fsanitize=address)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -fsanitize=address")
endif()



find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_subdirectory(lib/googletest)
add_subdirectory(lib/json-develop)
add_subdirectory(src)
add_subdirectory(tst)