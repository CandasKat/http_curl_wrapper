include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES "*.cpp")

add_library(http_curl_wrapper_lib ${SOURCES})
target_include_directories(http_curl_wrapper_lib PUBLIC ${CURL_INCLUDE_DIRS})
target_link_libraries(http_curl_wrapper_lib ${CURL_LIBRARIES})

add_executable(http_curl_wrapper ${SOURCES})
target_link_libraries(http_curl_wrapper http_curl_wrapper_lib CURL::libcurl)

