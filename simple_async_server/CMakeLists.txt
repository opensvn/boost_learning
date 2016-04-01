cmake_minimum_required(VERSION 2.8.4)
project(simple_async_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BOOST_DIR /root/boost)
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)

set(SOURCE_FILES main.cpp)
add_executable(simple_async_server ${SOURCE_FILES})
target_link_libraries(simple_async_server boost_system)