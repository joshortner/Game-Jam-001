cmake_minimum_required(VERSION 3.7.1)
set(CMAKE_CXX_STANDARD 20)
project(bullet_killer)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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

add_subdirectory(deps/sfml)

target_link_libraries(
    ${PROJECT_NAME}
    SFML
)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DBK_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")