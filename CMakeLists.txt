cmake_minimum_required(VERSION 3.12)
project(UnsignedBigInteger)

set(CMAKE_CXX_STANDARD 17)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()


# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

add_library(CustomInt CustomInt.cpp)

add_executable(play main.cpp)
target_link_libraries(play CustomInt)

enable_testing()

add_executable(cintUnitTests cint_tests.cpp)
target_link_libraries(cintUnitTests gtest gtest_main CustomInt)
add_test(cintUnitTests cintUnitTests)