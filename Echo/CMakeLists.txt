cmake_minimum_required(VERSION 2.6)
project(Echo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BOOST_DIR /root/boost)
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)

add_executable(tcp_sync_client tcp_sync_client.cpp)
add_executable(tcp_sync_server tcp_sync_server.cpp)
add_executable(tcp_async_client tcp_async_client.cpp)
add_executable(tcp_async_server tcp_async_server.cpp)

target_link_libraries(tcp_sync_client boost_system boost_thread)
target_link_libraries(tcp_sync_server boost_system boost_thread)
target_link_libraries(tcp_async_client boost_system boost_thread)
target_link_libraries(tcp_async_server boost_system boost_thread)