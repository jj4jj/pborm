#projects genearte by cmaketools 

#project(pborm CXX)
project(dcagent CXX)
set(pborm_VERSION 0.0.1)

#min version
cmake_minimum_required(VERSION 2.6)

# building must be in not source

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" BUILDING_IN_SOURCE)

if(BUILDING_IN_SOURCE)
	message(FATAL_ERROR "compile dir must not be source dir , please remove 'CMakeCache.txt' in current dir , then create a building dir in which dir you can exec commands like this 'cmake <src dir> [options]' ")
endif()

# compile option
option(DEBUG "Debug mode" 1)
option(PCH "Use precompiled headers" 0)
SET(DEBUG 1)


SET( CMAKE_VERBOSE_MAKEFILE on)

if(DEBUG)
	set(CMAKE_BUILD_TYPE Debug)
    add_definitions(-DDEBUG)
	message("Build in debug-mode : Yes (default)")
else()
	set(CMAKE_BUILD_TYPE Release)
	message("Build in debug-mode : No")
endif()

set(CMAKE_COMM_FLAGS "")
#debug common
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${CMAKE_COMM_FLAGS} -g3 -ggdb3 -Wall -Wfatal-errors -Wextra  -rdynamic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  ${CMAKE_COMM_FLAGS} -g3 -ggdb3 -Wall -Wfatal-errors -Wextra -std=c++11 -rdynamic")

# release mode
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${CMAKE_COMM_FLAGS} -g   -rdynamic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_COMM_FLAGS} -g -std=c++11  -rdynamic")

# output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# install dir
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

add_subdirectory(api)
add_subdirectory(orm)
add_subdirectory(testapi)



