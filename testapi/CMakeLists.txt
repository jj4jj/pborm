#projects genearte by cmaketools
#file(GLOB_RECURSE cur_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.c *.cc *.hpp)
#file(GLOB cur_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.c *.cc *.hpp)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} cur_aSRCS)
set(cur_SRCS "${cur_aSRCS}")


#base dir depend on itself and some otherlib
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}
/usr/local/include
${PROJECT_SOURCE_DIR}/3rd/dcpots)

#base dir linked lib dir
link_directories(
${PROJECT_SOURCE_DIR}/3rd/dcpots/lib
/usr/local/lib
${PROJECT_SOURCE_DIR}/lib)

#it will generate a exe

ADD_EXECUTABLE(testapi ${cur_SRCS})

#assign custrom link lib
target_link_libraries(testapi
pborm_api
dcnode
libprotobuf.a)

#installing
INSTALL(TARGETS testapi DESTINATION bin/)
