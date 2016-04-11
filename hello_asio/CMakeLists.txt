cmake_minimum_required(VERSION 2.8.4)
project(hello_asio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BOOST_DIR /root/boost)
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)

set(SERVER_SOURCE_FILES server.cpp)
add_executable(server ${SERVER_SOURCE_FILES})
target_link_libraries(server boost_system)

set(CLIENT_SOURCE_FILES client.cpp)
add_executable(client ${CLIENT_SOURCE_FILES})
target_link_libraries(client boost_system boost_thread)