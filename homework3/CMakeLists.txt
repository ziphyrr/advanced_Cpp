cmake_minimum_required(VERSION 3.0.0)
project(set)


set(CMAKE_CXX_STANDARD 17)

set(SET_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/set_project_dir/)
# file(GLOB HEADERS ${SET_INCLUDE_DIRS}/*.h)


add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${SET_INCLUDE_DIRS})

add_subdirectory(tests)
