cmake_minimum_required(VERSION 2.8.4)
project(button)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BOOST_DIR /root/boost)
include_directories(${BOOST_DIR})
link_directories(${BOOST_DIR}/stage/lib)

aux_source_directory(. SOURCE_FILES)
add_executable(button ${SOURCE_FILES})
target_link_libraries(button boost_system)