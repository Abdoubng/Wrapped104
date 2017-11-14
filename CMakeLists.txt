cmake_minimum_required(VERSION 3.0)

project(IEC60870)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

set(LIB_VERSION_MAJOR "0")
set(LIB_VERSION_MINOR "0")
set(LIB_VERSION_PATCH "1")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

include_directories(
${CMAKE_CURRENT_LIST_DIR}/src
${CMAKE_CURRENT_LIST_DIR}/lib104/
)

link_directories(
${CMAKE_CURRENT_LIST_DIR}/lib104/
)


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/example)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/python)

set(API_HEADERS
       src/server.hpp
       src/handlers.hpp
)       
