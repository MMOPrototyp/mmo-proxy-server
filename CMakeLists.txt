﻿# CMakeList.txt: CMake-Projekt für "mmo-proxy-server". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

project ("mmo-proxy-server")

add_definitions("-std=c++14")

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(build/conanbuildinfo.cmake)
conan_basic_setup()

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (mmo-proxy-server "mmo-proxy-server.cpp" "mmo-proxy-server.h")
target_link_libraries(mmo-proxy-server ${CONAN_LIBS})

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.