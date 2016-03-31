project(CLIENT)
cmake_minimum_required(VERSION 2.8)

set(BOOST_DIR /root/boost)
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)

add_executable(async_client async_client.cpp)
add_executable(sync_client sync_client.cpp)

target_link_libraries(async_client boost_system)
target_link_libraries(sync_client boost_system)
