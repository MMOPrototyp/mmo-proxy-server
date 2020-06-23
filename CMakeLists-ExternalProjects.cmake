include(ExternalProject)

# Builds external third party projects.
# The parent script needs to define the "GLOBAL_OUTPUT_PATH" variable,
# which will be used as output directory for all *.lib, *.dll, *.a, *.so, *.pdb files.

# see also: https://github.com/mfreiholz/cmake-example-external-project/blob/master/CMakeLists-ExternalProjects.txt

################################
# Redis Client (Header only)   #
################################

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/redis-cpp/include)

################################
# Boost Library                #
################################

#FIND_PACKAGE( Boost 1.73 COMPONENTS program_options REQUIRED )
#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# see also: https://stackoverflow.com/questions/15290386/using-boost-asio-with-cmake?rq=1

set (BOOST_MIN_VERSION "1.73.0")
#set (Boost_NO_BOOST_CMAKE ON)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system)
#find_package(Boost COMPONENTS asio)

#find_package(Boost 1.40.0 REQUIRED system)
#include_directories(${Boost_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

#message(NOTICE "Boost include path: " ${Boost_INCLUDE_DIR})

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Fatal error: Boost (version >= 1.55) required.")
else()
    message(STATUS "Setting up BOOST")
    #message(STATUS " Boost version: " ${Boost_VERSION})
    message(STATUS " Boost version: " ${Boost_MAJOR_VERSION} "." ${Boost_MINOR_VERSION} "." ${Boost_SUBMINOR_VERSION})
    #message(STATUS " Boost library version: " ${Boost_LIB_VERSION})
    message(STATUS " Includes - ${Boost_INCLUDE_DIRS}")
    message(STATUS " Library  - ${Boost_LIBRARY_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif (NOT Boost_FOUND)

################################
# JSON Library (Header only)   #
################################

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/json/include)

################################
# evpp Library                 #
################################

#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/evpp/apps)
#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/evpp/3rdparty)

#[[
ExternalProject_Add(
        EVPP

        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/evpp

        UPDATE_COMMAND ""
        PATCH_COMMAND ""

        #BUILD_COMMAND make

        SOURCE_DIR "${CMAKE_SOURCE_DIR}/3rdparty/evpp"
        CMAKE_ARGS -DBuildShared=ON -DBuildExamples=OFF -DCMAKE_INSTALL_PREFIX=${GLOBAL_OUTPUT_PATH}/evpp

        BUILD_IN_SOURCE 1
        BUILD_COMMAND make
        INSTALL_COMMAND make

        TEST_COMMAND ""
)

ExternalProject_Get_Property(EVPP BINARY_DIR)
ExternalProject_Get_Property(EVPP SOURCE_DIR)

#add_library(Config4CPP STATIC IMPORTED)
#set_target_properties(RedisCPPLibrary PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/lib/libcpp_redis.lib)

add_library(EVPPLibrary STATIC IMPORTED)
set_target_properties(EVPPLibrary PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/lib/libevpp.a)

message(NOTICE "EVPPLibrary source directory: " ${SOURCE_DIR})
message(NOTICE "EVPPLibrary binary directory: " ${BINARY_DIR})

]]

################################
# Wangle Library               #
################################

find_package(folly CONFIG REQUIRED)
#target_link_libraries(main PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

find_package(fizz CONFIG REQUIRED)
#target_link_libraries(main PRIVATE fizz::fizz)

find_package(wangle REQUIRED)
#target_link_libraries(main PRIVATE wangle::wangle)

################################
# Config Library               #
################################

#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/config/include)

# config4cpp

#[[
ExternalProject_Add(
        Config4CPP

        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/config4cpp

        UPDATE_COMMAND ""
        PATCH_COMMAND ""

        #BUILD_COMMAND make

        SOURCE_DIR "${CMAKE_SOURCE_DIR}/3rdparty/config4cpp"
        CMAKE_ARGS -DBuildShared=ON -DBuildExamples=OFF -DCMAKE_INSTALL_PREFIX=${GLOBAL_OUTPUT_PATH}/config4cpp

        BUILD_IN_SOURCE 1
        BUILD_COMMAND make
        INSTALL_COMMAND make

        TEST_COMMAND ""
)

ExternalProject_Get_Property(Config4CPP BINARY_DIR)
ExternalProject_Get_Property(Config4CPP SOURCE_DIR)

#add_library(Config4CPP STATIC IMPORTED)
#set_target_properties(RedisCPPLibrary PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/lib/libcpp_redis.lib)

add_library(Config4CPPLibrary STATIC IMPORTED)
set_target_properties(Config4CPPLibrary PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/lib/libconfig4cpp.a)

message(NOTICE "Config4CPPLibrary source directory: " ${SOURCE_DIR})
message(NOTICE "Config4CPPLibrary binary directory: " ${BINARY_DIR})
]]

#add_dependencies(Config4CPPLibrary Config4CPP)
#include_directories(${SOURCE_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/config4cpp/include)

add_library(Config4CPP STATIC IMPORTED)
set_target_properties(Config4CPP PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/3rdparty/config4cpp/lib/libconfig4cpp.a)
set_target_properties(Config4CPP PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/3rdparty/config4cpp/lib/libconfig4cpp.lib)

################################
# Ini Parser Library           #
################################

#[[
file(GLOB SOURCES
        ${CMAKE_SOURCE_DIR}/3rdparty/inih/cpp/*.h
        ${CMAKE_SOURCE_DIR}/3rdparty/inih/cpp/*.cpp
)
]]

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/inih/cpp)

################################
# Network Library tacopie      #
################################

# add the third party project
#[[
ExternalProject_Add(
        Tacopie

        GIT_REPOSITORY "https://github.com/cpp-redis/cpp_redis.git"
        GIT_TAG "master"

        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/cpp_redis

        UPDATE_COMMAND ""
        PATCH_COMMAND ""

        SOURCE_DIR "${CMAKE_SOURCE_DIR}/3rdparty/cpp_redis"
        CMAKE_ARGS -DBuildShared=ON -DBuildExamples=OFF -DCMAKE_INSTALL_PREFIX=${GLOBAL_OUTPUT_PATH}/cpp_redis

        TEST_COMMAND ""
)
]]

################################
# Redis Client                 #
################################

# redis_cpp

# add the third party project
#[[
ExternalProject_Add(
  RedisCPP

  GIT_REPOSITORY "https://github.com/cpp-redis/cpp_redis.git"
  GIT_TAG "master"

  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/cpp_redis
  
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/3rdparty/cpp_redis"
  CMAKE_ARGS -DBuildShared=ON -DBuildExamples=OFF -DCMAKE_INSTALL_PREFIX=${GLOBAL_OUTPUT_PATH}/cpp_redis
  
  TEST_COMMAND ""
)

#ExternalProject_Add_Step(
#  RedisCPP CopyToBin
#  COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLOBAL_OUTPUT_PATH}/cpp_redis/bin ${GLOBAL_OUTPUT_PATH}
#  COMMAND ${CMAKE_COMMAND} -E copy_directory ${GLOBAL_OUTPUT_PATH}/cpp_redis/lib ${GLOBAL_OUTPUT_PATH}
#  DEPENDEES install
#)

# stores dir to variable REDISCPP_BINARY_DIR
ExternalProject_Get_Property(RedisCPP BINARY_DIR)
ExternalProject_Get_Property(RedisCPP SOURCE_DIR)

#add_library(RedisCPPLibrary STATIC IMPORTED)
#set_target_properties(RedisCPPLibrary PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/lib/libcpp_redis.lib)

#add_dependencies(RedisCPPLibrary RedisCPP)

#message(WARNING ${SOURCE_DIR})
message(NOTICE "RedisCPPLibrary source directory: " ${SOURCE_DIR})
message(NOTICE "RedisCPPLibrary binary directory: " ${BINARY_DIR})

include_directories(${SOURCE_DIR}/includes)
include_directories(${SOURCE_DIR}/tacopie/includes)
]]