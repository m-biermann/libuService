cmake_minimum_required(VERSION 3.15)
project(libuService)

set(CMAKE_CXX_STANDARD 20)

add_library(libuService src/dummy.cpp include/de.mabiphmo/uService/settings.h include/de.mabiphmo/uService/resources/resource.h include/de.mabiphmo/uService/server/server.h include/de.mabiphmo/uService/server/session.h include/de.mabiphmo/uService/resources/resource_typed_body.h include/de.mabiphmo/uService/server/listener.h include/de.mabiphmo/uService/auth/auth_service.h include/de.mabiphmo/uService/auth/bearer_token.h)

include_directories(include)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(libuService ${BOOST_LIB_DIR})