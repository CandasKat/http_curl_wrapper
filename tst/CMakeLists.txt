include_directories(${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB TEST_SOURCES "*.cpp")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(http_curl_wrapper_tst ${TEST_SOURCES})
target_link_libraries(http_curl_wrapper_tst gtest gtest_main http_curl_wrapper_lib ${CURL_LIBRARIES})
