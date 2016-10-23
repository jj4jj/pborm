#projects genearte by cmaketools
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CSRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/orm/proto CSRCS)
list(APPEND CSRCS "${extra}")
list(APPEND CSRCS "${PROJECT_SOURCE_DIR}/")

#base dir depend on itself and some otherlib
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}
/usr/local/include
${PROJECT_SOURCE_DIR}/..
${PROJECT_SOURCE_DIR}/../pbdcex/include
${PROJECT_SOURCE_DIR}/../pbdcex/include)

#base dir linked lib dir
link_directories(
${PROJECT_SOURCE_DIR}/../dcpots/lib
${PROJECT_SOURCE_DIR}/../pbdcex/lib
/usr/local/lib
${PROJECT_SOURCE_DIR}/lib)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.pb.cc
COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/../orm && make
DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.proto
)
list(APPEND CSRCS ${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.pb.cc)

#it will generate a exe
ADD_EXECUTABLE(pborm ${CSRCS})

#assign custrom link lib
target_link_libraries(pborm
dcbase
dcnode
dcutil-mysql
pbdcex
libprotobuf.a
mysqlclient
dl
m
rt
pthread)

#installing
INSTALL(TARGETS pborm DESTINATION bin/)

