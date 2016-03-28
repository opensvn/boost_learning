cmake_minimum_required(VERSION 2.8.4)
project(http_sync_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BOOST_DIR /root/boost)
set(OBJ http_sync_client)

include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)

set(SOURCE_FILES main.cpp)
add_executable(${OBJ} ${SOURCE_FILES})
target_link_libraries(${OBJ} boost_system)