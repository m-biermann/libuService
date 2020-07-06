cmake_minimum_required(VERSION 3.15)
project(uService)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(uService include/mabiphmo/uService/settings.h include/mabiphmo/uService/resources/Resource.h include/mabiphmo/uService/server/Server.h include/mabiphmo/uService/server/Session.h include/mabiphmo/uService/resources/ResourceTypedBody.h include/mabiphmo/uService/auth/AuthService.h include/mabiphmo/uService/auth/BearerToken.h src/main.cpp src/construction/AppBuilder.cpp src/construction/AppBuilder.h src/construction/AppLayerBuilder.cpp src/construction/AppLayerBuilder.h include/mabiphmo/uService/construction/IAppLayerBuilder.h include/mabiphmo/uService/construction/IAppBuilder.h include/mabiphmo/uService/ioc/container.h src/listener/ListenerBase.cpp src/listener/ListenerBase.h src/listener/ClearTextListener.cpp src/listener/ClearTextListener.h src/listener/SslListener.cpp src/listener/SslListener.h)

include_directories(include)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(uService ${BOOST_LIB_DIR})