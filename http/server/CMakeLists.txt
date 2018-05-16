project(HTTP_SERVER)
cmake_minimum_required(VERSION 2.6)

#set(BOOST_DIR /root/boost)
#include_directories(${BOOST_DIR})
#link_directories(${BOOST_DIR}/stage/lib)

aux_source_directory(. SRC_LIST)
add_executable(http_server ${SRC_LIST})
target_link_libraries(http_server boost_system pthread)
