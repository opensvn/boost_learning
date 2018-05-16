project(hello_asio)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BOOST_DIR /usr/local/boost)
include_directories(${BOOST_DIR}/include)
link_directories(${BOOST_DIR}/lib)

set(SHARE_SRC flag.cpp)

set(SERVER_SOURCE_FILES server.cpp)
add_executable(server ${SERVER_SOURCE_FILES} ${SHARE_SRC})
target_link_libraries(server
  boost_system
  boost_thread)

add_executable(recv recv.cpp ${SHARE_SRC})
target_link_libraries(recv
  boost_system
  boost_thread)

set(CLIENT_SOURCE_FILES client.cpp)
add_executable(client ${CLIENT_SOURCE_FILES} ${SHARE_SRC})
target_link_libraries(client
  boost_system
  boost_thread)

add_executable(send send.cpp ${SHARE_SRC})
target_link_libraries(send
  boost_system
  boost_thread)
