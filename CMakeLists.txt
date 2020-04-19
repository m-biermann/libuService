cmake_minimum_required(VERSION 3.15)
project(libuService)

set(CMAKE_CXX_STANDARD 20)

add_library(libuService src/dummy.cpp include/settings.h include/model/resource.h include/model/server.h include/model/session.h include/model/resource_typed_body.h include/model/listener.h)

include_directories(include)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(libuService ${BOOST_LIB_DIR})