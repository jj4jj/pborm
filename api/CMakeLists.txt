
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} cur_aSRCS)
set(cur_SRCS "${cur_aSRCS}")

aux_source_directory(${PROJECT_SOURCE_DIR}/orm/proto cur_aSRCS)
set(cur_SRCS "${cur_SRCS};${cur_aSRCS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}
/usr/include
/usr/local/include
${PROJECT_SOURCE_DIR}/3rd/dcpots)

add_library(pborm_api STATIC ${cur_SRCS})

link_directories(/usr/local/lib
/usr/local/lib)

target_link_libraries(pborm_api
)

