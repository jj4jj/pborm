#projects genearte by cmaketools
#file(GLOB_RECURSE cur_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.c *.cc *.hpp)
#file(GLOB cur_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp *.c *.cc *.hpp)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} cur_aSRCS)
set(cur_SRCS "${cur_aSRCS}")
aux_source_directory(${PROJECT_SOURCE_DIR}/orm/proto cur_aSRCS)
set(cur_SRCS "${cur_SRCS};${cur_aSRCS}")
set(cur_SRCS "${cur_SRCS};${PROJECT_SOURCE_DIR}/3rd/hpbex/ext_meta.cpp")
set(cur_SRCS "${cur_SRCS};${PROJECT_SOURCE_DIR}/3rd/hpbex/mysql_gen.cpp")
set(cur_SRCS "${cur_SRCS};${PROJECT_SOURCE_DIR}/3rd/hpbex/extensions_option.cpp")

#base dir depend on itself and some otherlib
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}
/usr/local/include
${PROJECT_SOURCE_DIR}/3rd/dcpots
${PROJECT_SOURCE_DIR}/3rd/hpbex)

#base dir linked lib dir
link_directories(
${PROJECT_SOURCE_DIR}/3rd/dcpots/lib
/usr/local/lib
${PROJECT_SOURCE_DIR}/lib)

#it will generate a exe

ADD_EXECUTABLE(pborm ${cur_SRCS})

#assign custrom link lib
target_link_libraries(pborm
dcnode
dcutil
libprotobuf.a
mysqlclient)

#installing
INSTALL(TARGETS pborm DESTINATION bin/)
