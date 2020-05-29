# CMakeList.txt: CMake-Projekt für "mmo-proxy-server". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

project (ProxyServer VERSION 1.0.0)
configure_file(ProxyConfig.h.in ProxyConfig.h)

add_definitions("-std=c++17")

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(build/conanbuildinfo.cmake)
conan_basic_setup()

#add_subdirectory(src)
#add_subdirectory(test)

# 3rdparty Libraries
include(CMakeLists-ExternalProjects.cmake)

include_directories(src)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (ProxyServer "mmo-proxy-server.cpp" "mmo-proxy-server.h" src/RedisClient.cpp src/RedisClient.h)
target_link_libraries(ProxyServer ${CONAN_LIBS})

target_include_directories(ProxyServer PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

#target_link_libraries(ProxyServer RedisCPPLibrary)

# Boost Library
#target_link_libraries( anyExecutable LINK_PUBLIC ${Boost_LIBRARIES} )

target_link_libraries(ProxyServer ${Boost_LIBRARIES})

# threading system for Boost
#target_link_libraries(ProxyServer ${CMAKE_THREAD_LIBS_INIT})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ProxyServer Threads::Threads)

#target_link_libraries(ProxyServer Config4CPPLibrary)
target_link_libraries(ProxyServer Config4CPP)

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
