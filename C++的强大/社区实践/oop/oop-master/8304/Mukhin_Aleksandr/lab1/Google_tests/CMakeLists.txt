project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run test.cpp)
include_directories(../headers)
# linking Google_Tests_run with headers which will be tested
target_link_libraries(Google_Tests_run headers gtest gtest_main)
