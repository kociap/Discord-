set(SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/activity.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/auth.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/channel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/client.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gateway.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/guild.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/message.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/presence.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/relationship.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/user.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/usersettings.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/userguildsettings.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/urls.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/image.cpp"
)

set(HEADER_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/activity.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/auth.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/channel.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/client.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gateway.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/guild.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/message.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/opcodes.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/presence.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/relationship.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/types.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/urls.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/user.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/usersettings.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/data/userguildsettings.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/image.hpp"
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} PUBLIC ${HEADER_FILES})

