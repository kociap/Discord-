set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/guildicon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/guildslist.cpp
)

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/guildicon.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/guildslist.hpp
)

set(UI_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/guildicon.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/guildslist.ui
)

target_sources(${PROJECT_NAME}
    PRIVATE ${SOURCE_FILES}
    PUBLIC ${HEADER_FILES} ${UI_FILES}
)
