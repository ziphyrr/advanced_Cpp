cmake_minimum_required(VERSION 3.14)
project(set_test)

file(GLOB SOURCES *.cpp)

add_subdirectory(googletest)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SET_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} set GTest::gtest_main)
