project(Discord_Wrapper)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${PROJECT_NAME})

set(SOURCE_FILES)
set(HEADER_FILES)

add_subdirectory(discord)

target_sources(${PROJECT_NAME} 
    PRIVATE ${SOURCE_FILES} 
    PUBLIC ${HEADER_FILES}
)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
    # PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/discord"
)

target_link_libraries(${PROJECT_NAME}
    nlohmann_json::nlohmann_json
    rpp 
)

