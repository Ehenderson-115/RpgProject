cmake_minimum_required(VERSION 3.10)

project(RpgGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header File for cmake defines
configure_file(RpgGameConfig.h.in RpgGameConfig.h)


add_subdirectory(GameObjects)

list(APPEND GAME_OBJECTS GameObjects)

add_subdirectory(GameCommands)

list(APPEND GAME_COMMANDS GameCommands)


install(FILES config.txt DESTINATION Assets)


add_executable(${PROJECT_NAME} rpgGame.cpp)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})

target_link_libraries(${PROJECT_NAME} PUBLIC ${GAME_OBJECTS} ${GAME_COMMANDS})

target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
