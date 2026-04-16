  cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")


project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

# external dependencies with FetchContent
include(FetchContent)

set(FETCHCONTENT_QUIET OFF CACHE INTERNAL "Override verbose output" FORCE)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE INTERNAL "Override update strategy" FORCE)
set(SFML_WARNINGS_AS_ERRORS OFF)

# NOTE: Also update SFML_VERSION and other env vars used for caching in
#     - .github/actions/configure-cmake/action.yml
#     - .github/workflows/cmake.yml
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    # renovate: datasource=github-tags depName=SFML/SFML versioning=loose
    GIT_TAG        3.0.2
    # renovate: depName=SFML/SFML
    # GIT_TAG        0fa201c969e48ecc253581c5841ce73f44d42f49 # 3.0.2
    GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
    GIT_PROGRESS   ON
)

FetchContent_MakeAvailable(SFML)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
    main.cpp
        src/uis/ui.cpp
        include/ui.h
        src/graphic_functions.cpp
        include/graphic_functions.h
        src/world_generator.cpp
        include/world_generator.h
        src/chunk.cpp
        include/chunk.h
        src/perlin_noise.cpp
        include/perlin_noise.h
        src/graphic_engine.cpp
        include/graphic_engine.h
        src/chunk_loader.cpp
        include/chunk_loader.h
        include/structures.h
        src/game_engine.cpp
        include/game_engine.h
        src/ui_system.cpp
        include/ui_system.h
        src/uis/ui_window.cpp
        include/ui_window.h
        include/ui_render_functions.h
        src/ui_render_functions.cpp
        src/ui_style.cpp
        include/ui_style.h
        src/uis/ui_section.cpp
        include/ui_section.h
        src/uis/ui_button.cpp
        include/ui_button.h
        src/ui_actions.cpp
        include/ui_actions.h
        src/event_handler.cpp
        include/event_handler.h
        src/events/event.cpp
        include/event.h
        include/key_event.h
        src/events/key_event.cpp
        include/string_functions.h
        src/string_functions.cpp
        src/ui_constructor.cpp
        include/ui_constructor.h
        ext/tiny-xml2/tinyxml2.cpp
        ext/tiny-xml2/tinyxml2.h
        src/player.cpp
        include/player.h
        src/uis/ui_item_tile.cpp
        include/ui_item_tile.h
        src/item.cpp
        include/item.h
        src/uis/ui_item_tile_grid.cpp
        include/ui_item_tile_grid.h
        src/events/mouse_event.cpp
        include/mouse_event.h
        src/ui_binder.cpp
        include/ui_binder.h
        src/events/ui_event.cpp
        include/ui_event.h
        src/events/generic_event.cpp
        include/generic_event.h
        src/uis/interface_ui.cpp
        include/interface_ui.h
        src/uis/container_ui.cpp
        include/container_ui.h
        src/action_handler.cpp
        include/action_handler.h
        src/build_system.cpp
        include/build_system.h
        src/collision_handler.cpp
        src/collision_handler.h
)
target_sources(${MAIN_EXECUTABLE_NAME}
    PRIVATE
        src/Example.cpp
)

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS ${USE_ASAN} TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
# set_compiler_flags(TARGET_NAMES ${MAIN_EXECUTABLE_NAME} ${FOO} ${BAR})
# where ${FOO} and ${BAR} represent additional executables or libraries
# you want to compile with the set compiler flags

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${MAIN_EXECUTABLE_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE
    ext
)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE
    SFML::Graphics SFML::Window SFML::System Threads::Threads
)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE X11)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt DIRECTORY assets COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
