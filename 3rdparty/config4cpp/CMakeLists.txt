cmake_minimum_required(VERSION 2.8.7)
set(CMAKE_MACOSX_RPATH 1)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)


###
# project
###
set(PROJECT config4cpp)
project(${PROJECT} CXX)


set(CPP_CONFIG4CPP_INCLUDES ${PROJECT_SOURCE_DIR}/include)

###
# includes
###
include_directories(${CPP_CONFIG4CPP_INCLUDES})


###
# sources
###
set(SRC_DIRS "src")

foreach (dir ${SRC_DIRS})
	# get directory sources and headers
	file(GLOB s_${dir} "${dir}/*.cpp")
	file(GLOB h_${dir} "${dir}/*.h")
	file(GLOB h_${dir} "${dir}/*.hpp")
	file(GLOB i_${dir} "${dir}/*.ipp")

	# set sources
	set(SOURCES ${SOURCES} ${s_${dir}} ${h_${dir}} ${i_${dir}})
endforeach ()


###
# outputs
###
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_PKGCONFIG_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

###
# executable
###
add_library(${PROJECT} ${SOURCES})
set_property(TARGET ${PROJECT} PROPERTY POSITION_INDEPENDENT_CODE ON)

#[[
if (WIN32)
	set_target_properties(${PROJECT}
						  PROPERTIES COMPILE_PDB_NAME ${PROJECT}
						  COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif (WIN32)
]]


###
# install
###
# ensure lib and bin directories exist
install(CODE "FILE(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})")
install(CODE "FILE(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})")
# install cpp_redis
install(DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ DESTINATION lib USE_SOURCE_PERMISSIONS)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ DESTINATION bin USE_SOURCE_PERMISSIONS)
install(DIRECTORY ${CPP_CONFIG4CPP_INCLUDES}/ DESTINATION include USE_SOURCE_PERMISSIONS)
