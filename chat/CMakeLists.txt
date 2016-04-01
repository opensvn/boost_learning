cmake_minimum_required(VERSION 2.8.4)
project(chat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BOOST_DIR /root/boost)
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)

add_executable(chat_client chat_client.cpp chat_message.hpp)
add_executable(chat_server chat_server.cpp chat_message.hpp)

target_link_libraries(chat_client boost_system boost_thread)
target_link_libraries(chat_server boost_system boost_thread)