include(ExternalProject)

# Builds external third party projects.
# The parent script needs to define the "GLOBAL_OUTPUT_PATH" variable,
# which will be used as output directory for all *.lib, *.dll, *.a, *.so, *.pdb files.

# see also: https://github.com/mfreiholz/cmake-example-external-project/blob/master/CMakeLists-ExternalProjects.txt

################################
# Redis Client                 #
################################

# redis_cpp

# add the third party project
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
#ExternalProject_Get_Property(RedisCPP REDISCPP_BINARY_DIR)
ExternalProject_Get_Property(RedisCPP BINARY_DIR)
ExternalProject_Get_Property(RedisCPP SOURCE_DIR)

#set_target_properties(RedisCPP PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/...)
#set_target_properties(RedisCPP PROPERTIES IMPORTED_LOCATION ${GLOBAL_OUTPUT_PATH}/cpp_redis/bin)

add_library(RedisCPPLibrary STATIC IMPORTED)
set_target_properties(RedisCPPLibrary PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/lib/libcpp_redis.a)

#add_library(RedisCPPLibrary STATIC IMPORTED)

#add_library(
#    RedisCPPLibrary STATIC "${CMAKE_SOURCE_DIR}/3rdparty/cpp_redis"
#)

add_dependencies(RedisCPPLibrary RedisCPP)

include_directories(${SOURCE_DIR}/includes)