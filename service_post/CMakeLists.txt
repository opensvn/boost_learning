cmake_minimum_required(VERSION 2.8.4)
project(service_post)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BOOST_DIR /root/boost)
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)

set(SOURCE_FILES main.cpp)
add_executable(service_post ${SOURCE_FILES})
target_link_libraries(service_post boost_system boost_thread)