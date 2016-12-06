project(tests)

add_subdirectory(../../gtest gtest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(runTests
        SmartPointerTests.cpp
        SharedPointerTests.cpp)

target_link_libraries(runTests gtest gtest_main)