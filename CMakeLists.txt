cmake_minimum_required(VERSION 3.15)
project(uService)

set(CMAKE_CXX_STANDARD 20)

add_library(uService include/mabiphmo/uService/settings.h include/mabiphmo/uService/resources/Resource.h include/mabiphmo/uService/server/Server.h include/mabiphmo/uService/server/Session.h include/mabiphmo/uService/resources/ResourceTypedBody.h include/mabiphmo/uService/server/Listener.h include/mabiphmo/uService/auth/AuthService.h include/mabiphmo/uService/auth/BearerToken.h src/main.cpp src/construction/AppBuilder.cpp src/construction/AppBuilder.h src/construction/AppLayerBuilder.cpp src/construction/AppLayerBuilder.h include/mabiphmo/uService/construction/IAppLayerBuilder.h include/mabiphmo/uService/construction/IAppBuilder.h)

include_directories(include)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(uService ${BOOST_LIB_DIR})