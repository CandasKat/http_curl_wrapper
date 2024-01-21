include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES "*.cpp")

add_library(http_curl_wrapper_lib ${SOURCES})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_executable(http_curl_wrapper ${SOURCES})
target_link_libraries(http_curl_wrapper_lib CURL::libcurl)