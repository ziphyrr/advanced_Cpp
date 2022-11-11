cmake_minimum_required(VERSION 3.14)
project(matrix_calc_test)

file(GLOB SOURCES *.cpp)

add_subdirectory(googletest)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_CALC_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${MATRIX_CALC_LIBRARIES} GTest::gtest_main)