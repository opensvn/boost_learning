cmake_minimum_required(VERSION 2.8.4)
project(http_server1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BOOST_DIR /root/boost)
set(TARGET http_server)
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)

aux_source_directory(. SOURCE_FILES)

add_executable(${TARGET} ${SOURCE_FILES} connection.hpp)
target_link_libraries(${TARGET} boost_system)