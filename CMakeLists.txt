# CMakeList.txt: CMake-Projekt für "mmo-proxy-server". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

project (ProxyServer VERSION 1.0.0)
configure_file(ProxyConfig.h.in ProxyConfig.h)

add_definitions("-std=c++14")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
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
add_executable (ProxyServer "mmo-proxy-server.cpp" "mmo-proxy-server.h")
target_link_libraries(ProxyServer ${CONAN_LIBS})

target_include_directories(ProxyServer PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
