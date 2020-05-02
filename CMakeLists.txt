cmake_minimum_required(VERSION 3.15)
project(libuService)

set(CMAKE_CXX_STANDARD 20)

add_library(libuService src/dummy.cpp include/settings.h include/resources/resource.h include/server/server.h include/server/session.h include/resources/resource_typed_body.h include/server/listener.h include/auth/auth_service.h include/auth/bearer_token.h)

include_directories(include)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(libuService ${BOOST_LIB_DIR})