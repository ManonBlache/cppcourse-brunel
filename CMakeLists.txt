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
add_executable (network_unittest Neuron.cpp Network.cpp network_unittest.cpp)
add_executable (network_main Neuron.cpp Network.cpp network_main.cpp)

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest neuron_unitest)

target_link_libraries(network_unittest gtest gtest_main)
add_test(network_unittest network_unitest)

###### Doxygen generation ######

# We first check if Doxygen is present.
find_package(Doxygen)
if(DOXYGEN_FOUND)

    # We then check if the Doxygen.in configuration file exists
    IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in not found.
         - Generate one in the project folder with doxygen -g Doxyfile.in")
    ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

    # We configure the doxyfile for make.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)

