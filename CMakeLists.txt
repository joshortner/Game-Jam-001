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
    src/scene/scene.cpp
    src/application/application.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    # deps
    deps/sfml/include

    # bullet killer
    src
)

# Do a for each loop here
set(SFML_LIBRARIES)
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    message("Using Debug libraries.")
    find_library(SFML_GRAPHICS_LIB sfml-graphics-d HINTS ${CMAKE_SOURCE_DIR}/deps/sfml/build/lib/)
    find_library(SFML_WINDOW_LIB   sfml-window-d HINTS ${CMAKE_SOURCE_DIR}/deps/sfml/build/lib/)
    find_library(SFML_SYSTEM_LIB   sfml-system-d HINTS ${CMAKE_SOURCE_DIR}/deps/sfml/build/lib/)
    list(APPEND SFML_LIBRARIES ${SFML_GRAPHICS_LIB} ${SFML_WINDOW_LIB} ${SFML_SYSTEM_LIB})
else()
    message("Using Release libraries.")
    find_library(SFML_GRAPHICS_LIB sfml-graphics HINTS ${CMAKE_SOURCE_DIR}/deps/sfml/build/lib/)
    find_library(SFML_WINDOW_LIB   sfml-window HINTS ${CMAKE_SOURCE_DIR}/deps/sfml/build/lib/)
    find_library(SFML_SYSTEM_LIB   sfml-system HINTS ${CMAKE_SOURCE_DIR}/deps/sfml/build/lib/)
    list(APPEND SFML_LIBRARIES ${SFML_GRAPHICS_LIB} ${SFML_WINDOW_LIB} ${SFML_SYSTEM_LIB})
endif()

target_link_libraries(
    ${PROJECT_NAME}
    ${SFML_LIBRARIES}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DBK_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")