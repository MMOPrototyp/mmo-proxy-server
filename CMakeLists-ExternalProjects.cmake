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

################################
# Config Library               #
################################

include_directories(${CMAKE_SOURCE_DIR}/3rdparty/config/include)

################################
# Ini Parser Library           #
################################

#[[
file(GLOB SOURCES
        ${CMAKE_SOURCE_DIR}/3rdparty/inih/cpp/*.h
        ${CMAKE_SOURCE_DIR}/3rdparty/inih/cpp/*.cpp
)
]]

#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/inih/cpp)

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