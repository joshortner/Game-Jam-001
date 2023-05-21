cmake_minimum_required(VERSION 3.7.1)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(deps/flecs)

project(bullet_killer)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/bullet_killer.cpp
    #src/object_manager/object_npc.cpp
    #src/object_manager/object_mgr.cpp
    src/object_manager/object_player.cpp
    #src/object_manager/object_button.cpp
    #src/object_manager/object_room.cpp
    #src/object_manager/object_bullet.cpp
    #src/object_manager/object_enemy.cpp
    #src/object_manager/object_person.cpp
    #src/object_manager/object_text.cpp
    src/application/application.cpp
    src/animation/animation_system.cpp
    src/animation/node_interface.cpp
    #src/systems/hover_system.cpp
    #src/systems/bullet_system.cpp
    #src/systems/room_system.cpp
    src/systems/physics_system.cpp
    src/systems/enemy_system.cpp

    # Scenes
    src/scene/scene.cpp
    #src/scene/test_scene.cpp
    #src/scene/main_menu_scene.cpp
    src/scene/ecs_scene.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    # deps
    deps/sfml/include
    deps/SimplexNoise/src
    deps/flecs/include

    # bullet killer
    src
    src/object_manager
    src/scene
    src/application
    src/utility
    src/event
    src/systems
)

add_library(noise deps/SimplexNoise/src/SimplexNoise.cpp)

# Do a for each loop here
set(SFML_LIBRARIES)
set(SFML_BASE_DIR ${CMAKE_SOURCE_DIR}/deps/sfml/build/lib/)
set(SFML_DIRECTORIES ${SFML_BASE_DIR} ${SFML_BASE_DIR}/Debug)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    message("Using Debug libraries.")
    find_library(SFML_GRAPHICS_LIB sfml-graphics-d.lib HINTS  ${SFML_DIRECTORIES})
    find_library(SFML_WINDOW_LIB   sfml-window-d.lib HINTS ${SFML_DIRECTORIES})
    find_library(SFML_SYSTEM_LIB   sfml-system-d.lib HINTS ${SFML_DIRECTORIES})
    list(APPEND SFML_LIBRARIES ${SFML_GRAPHICS_LIB} ${SFML_WINDOW_LIB} ${SFML_SYSTEM_LIB})
else()
    message("Using Release libraries.")
    find_library(SFML_GRAPHICS_LIB sfml-graphics HINTS ${SFML_DIRECTORIES})
    find_library(SFML_WINDOW_LIB   sfml-window HINTS ${SFML_DIRECTORIES})
    find_library(SFML_SYSTEM_LIB   sfml-system HINTS ${SFML_DIRECTORIES})
    list(APPEND SFML_LIBRARIES ${SFML_GRAPHICS_LIB} ${SFML_WINDOW_LIB} ${SFML_SYSTEM_LIB})
endif()

target_link_libraries(
    ${PROJECT_NAME}
    ${SFML_LIBRARIES}
    flecs::flecs_static
    noise
)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DBK_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")