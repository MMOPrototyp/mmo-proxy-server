# CMakeList.txt: CMake-Projekt für "mmo-proxy-server". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.16)

project (ProxyServer VERSION 1.0.0)
configure_file(ProxyConfig.h.in ProxyConfig.h)

# does not work with MSVC
#add_definitions("-std=c++17")

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
endif()

# set C++17 for MSVC
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif(MSVC)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(build/conanbuildinfo.cmake)
conan_basic_setup()

#set(VCPKG_TARGET_ARCHITECTURE x64)
#set(VCPKG_CRT_LINKAGE dynamic)
#set(VCPKG_LIBRARY_LINKAGE dynamic)

#add_subdirectory(src)
#add_subdirectory(test)

# 3rdparty Libraries
include(CMakeLists-ExternalProjects.cmake)

include_directories(src)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (ProxyServer "mmo-proxy-server.cpp" "mmo-proxy-server.h" src/RedisClient.cpp src/RedisClient.h src/ServerConfig.cpp src/ServerConfig.h src/monitoring/MonitoringClient.cpp src/monitoring/MonitoringClient.h src/proxy/ProxyServer.cpp src/proxy/ProxyServer.h src/proxy/TCPServer.cpp src/proxy/TCPServer.h src/proxy/TCPSession.cpp src/proxy/TCPSession.h src/proxy/TCPMessage.cpp src/proxy/TCPMessage.h)
add_executable(Monitoring "src/monitoring/MonitoringMain.cpp" src/monitoring/MonitoringMain.h src/RedisClient.cpp src/RedisClient.h src/ServerConfig.cpp src/ServerConfig.h src/monitoring/MonitoringClient.cpp src/monitoring/MonitoringClient.h)
target_link_libraries(ProxyServer ${CONAN_LIBS})
target_link_libraries(Monitoring ${CONAN_LIBS})

find_package(folly CONFIG REQUIRED)
target_link_libraries(ProxyServer Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

find_package(fizz CONFIG REQUIRED)
target_link_libraries(ProxyServer fizz::fizz)

find_package(wangle REQUIRED)
target_link_libraries(ProxyServer wangle::wangle)

#set_property(TARGET ProxyServer PROPERTY CXX_STANDARD 17)

target_include_directories(ProxyServer PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

target_include_directories(Monitoring PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#target_link_libraries(ProxyServer RedisCPPLibrary)

# Boost Library
#target_link_libraries( anyExecutable LINK_PUBLIC ${Boost_LIBRARIES} )

target_link_libraries(ProxyServer ${Boost_LIBRARIES})
target_link_libraries(Monitoring ${Boost_LIBRARIES})

# threading system for Boost
#target_link_libraries(ProxyServer ${CMAKE_THREAD_LIBS_INIT})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ProxyServer Threads::Threads)
target_link_libraries(Monitoring Threads::Threads)

#target_link_libraries(ProxyServer Config4CPPLibrary)
target_link_libraries(ProxyServer Config4CPP)
target_link_libraries(Monitoring Config4CPP)

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
