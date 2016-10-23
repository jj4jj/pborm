aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CSRCS)

aux_source_directory(${PROJECT_SOURCE_DIR}/orm/proto CSRCS)
list(APPEND CSRCS "${extra}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}
/usr/include
/usr/local/include
${PROJECT_SOURCE_DIR}/..)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.pb.cc
COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/../orm && make
DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.proto
)
list(APPEND CSRCS ${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.pb.cc)

add_library(pborm_api STATIC ${CSRCS})

link_directories(
/usr/local/lib)

target_link_libraries(pborm_api
)


