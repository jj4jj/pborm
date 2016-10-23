#projects genearte by cmaketools
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CSRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/orm/proto CSRCS)
list(APPEND CSRCS "${extra}")
list(APPEND CSRCS "${PROJECT_SOURCE_DIR}/")

#base dir depend on itself and some otherlib
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}
/usr/local/include
${PROJECT_SOURCE_DIR}/..)

#base dir linked lib dir
link_directories(
${PROJECT_SOURCE_DIR}/../dcpots/lib
/usr/local/lib
${PROJECT_SOURCE_DIR}/lib)


#it will generate a exe
ADD_EXECUTABLE(testapi ${CSRCS})

#assign custrom link lib
target_link_libraries(testapi
dcbase
dcnode
pborm_api
dcutil-mysql
libprotobuf.a
mysqlclient
dl
m
rt
pthread)

#installing
INSTALL(TARGETS testapi DESTINATION bin/)

