cmake_minimum_required(VERSION 3.12)
project(Discordpp)

enable_language(CXX)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files.
set(CMAKE_AUTOUIC ON)

# Find the Qt libraries
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5WebEngineWidgets CONFIG REQUIRED)

# Source files
set(DISCORDPP_SRC
  "${CMAKE_CURRENT_SOURCE_DIR}/source/discordclient.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/source/driftuistyle.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/source/mainwindow.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/source/loginwindow.cpp"
)

set(DISCORDPP_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/source/discordclient.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/source/driftuistyle.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/source/mainwindow.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/source/loginwindow.hpp"
)

# Manually list all .ui files so that Qt Creator lists them in the projects view
set(UI_FILES
  source/mainwindow.ui
  source/loginwindow.ui
)

# add executable
add_executable(${PROJECT_NAME} ${DISCORDPP_SRC} ${DISCORDPP_HEADERS})
target_sources(${PROJECT_NAME} PUBLIC ${UI_FILES})

# Add certain include dirs manually because compiler can't find them
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC websocketpp asio/asio/include)

# add generated include directory
#target_compile_options(${PROJECT_NAME} PRIVATE -isystem ${PROJECT_NAME}_autogen/include)

set(CMAKE_USE_OPENSSL ON CACHE BOOL "" FORCE) # OPENSSL_ROOT_DIR must be set manually
if(CMAKE_USE_OPENSSL AND NOT OPENSSL_ROOT_DIR)
  message(FATAL_ERROR 
    "Please define OPENSSL_ROOT_DIR as the path to your OpenSSL build"
  )
endif()

set(BUILD_SHARED_LIBS CACHE BOOL OFF) # build all submodules as static libs
set(BUILD_TESTING CACHE BOOL OFF)

add_subdirectory(websocketpp)
add_subdirectory(json)
add_subdirectory(rpp)
add_subdirectory(source/discord)
add_subdirectory(source/widgets)

#extra flags
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  #general warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g")
  #special warnings for gcc
  if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas -Wodr -Wshadow -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -Wlogical-op -Warray-bounds=2 -Wimplicit-fallthrough=5 -Walloc-zero -Wduplicated-branches -Wduplicated-cond -Wplacement-new=2 -Wrestrict -Wold-style-cast -Wzero-as-null-pointer-constant -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Wformat-signedness -Wsuggest-attribute=noreturn -Wsuggest-attribute=format")
  endif()
  #special warnings for clang
  if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-newline-eof -Wno-padded -Wno-sign-conversion -Wno-exit-time-destructors -Wno-global-constructors -Wno-weak-vtables -Wno-c99-extensions -Wno-shorten-64-to-32 -Wno-range-loop-analysis -Wno-switch-enum -Wno-old-style-cast -Wodr -Wshadow -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -Warray-bounds -Wimplicit-fallthrough -Wduplicate-enum -Wold-style-cast -Wformat=2 -Wno-error=documentation-unknown-command -Wno-error=documentation-pedantic -Wno-error=reserved-id-macro -Wno-error=covered-switch-default -Wno-error=shadow-field-in-constructor")
    if (DEFINED ENV{TRAVIS})
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unreachable-code") #temporarily disable unreachable warning for clang-6.0.1
    endif()
  endif()
  #disable annoying warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-unused-variable -Wno-missing-braces")
  #set some warnings as not errors
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=unknown-pragmas -Wno-error=missing-prototypes -Wno-error=shadow -Wno-error=conversion -Wno-error=missing-declarations")
  #stop clang from complaining about unused flags. TODO: figure out why those flags are considered unused.
  if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
  endif()
  #extra debug flags
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -ggdb -O0")
  #environment flags
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} $ENV{CXX_FLAGS_DEBUG}")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} $ENV{CXX_LFLAGS_DEBUG}")
  #release flags
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} $ENV{CXX_FLAGS_RELEASE} -DNDEBUG")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} $ENV{CXX_LFLAGS_RELEASE}")
  #link time optimization for gcc only because of gold linker issues
  if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")
  endif()
  #disable warnings for generated files
  set_source_files_properties(
      ${PROJECT_NAME}_autogen/mocs_compilation.cpp
      PROPERTIES COMPILE_FLAGS -w
  )
endif()

# MSVC flags
if(MSVC)
  # warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
  # Disable some of the 4th level and all level warnings
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4127") # conditional expression is constant
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4710 /wd4711") # function inlining
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4820") # bytes padding added
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4625 /wd4626 /wd5026 /wd5027") # ctor implicitly deleted
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4514") # unreferenced function removed
endif()

# Find includes in corresponding build directories
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${CMAKE_CURRENT_SOURCE_DIR} -isystem ${CMAKE_CURRENT_BINARY_DIR}")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /I ${CMAKE_CURRENT_SOURCE_DIR}")
endif()
set(CMAKE_INCLUDE_CURRENT_DIR ON) #redundant, but required for Qt Creator to find generated files

# Other files one would want to edit that are not directly part of the SCE build but we want to appear in projects
set(MISC_FILES
  .clang-format
  .gitignore
  .travis.yml
  CMakeLists.txt
  README.md
)
add_custom_target(MISC_FILES
  COMMENT "This target only exists to list files in IDEs"
  SOURCES ${MISC_FILES} ${UI_FILES}
)

# Link executable
set(LIBS_TO_LINK
  Qt5::Widgets
  Qt5::WebEngineWidgets
  rpp
  nlohmann_json::nlohmann_json
)
target_link_libraries(${PROJECT_NAME} ${LIBS_TO_LINK})
