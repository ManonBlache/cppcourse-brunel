cmake_minimum_required (VERSION 2.6)
project (Neuron)

set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (test1 Neuron.cpp Network.cpp test1.cpp)
add_executable (test2 Neuron.cpp Network.cpp test2.cpp)
add_executable (test3 Neuron.cpp Network.cpp test3.cpp)
add_executable (test4 Neuron.cpp Network.cpp test4.cpp)
add_executable (neuron_unittest Neuron.cpp Network.cpp neuron_unittest.cpp)

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest neuron_unitest)
