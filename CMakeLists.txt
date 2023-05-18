cmake_minimum_required(VERSION 3.7.1)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(bullet_killer)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/bullet_killer.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    # deps
    deps/sfml/include

    # bullet killer
    src
)

target_link_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/deps/sfml/build/lib/Debug
)

target_link_libraries(
    ${PROJECT_NAME}
    sfml-graphics-d.lib sfml-window-d.lib sfml-system-d.lib
)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DBK_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")