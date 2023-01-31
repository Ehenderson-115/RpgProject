cmake_minimum_required(VERSION 3.10)

project(RpgGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header File for cmake changes (Unused)
configure_file(RpgGameConfig.h.in RpgGameConfig.h)


add_subdirectory(GameObjects)
list(APPEND GAME_OBJECTS GameObjects)

add_executable(RpgGame rpgGame.cpp)

target_link_libraries(RpgGame PUBLIC ${GAME_OBJECTS})

target_include_directories(RpgGame PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
