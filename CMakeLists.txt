cmake_minimum_required(VERSION 3.10)

project(RpgGame VERSION 1.0)

set(SERVER_NAME RpgGameServer)
set(CLIENT_NAME RpgGameClient)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Header File for cmake defines
configure_file(RpgGameConfig.h.in RpgGameConfig.h)

add_subdirectory(GameObjects)

list(APPEND GAME_OBJECTS GameObjects)

add_subdirectory(GameCommands)

list(APPEND GAME_COMMANDS GameCommands)

add_executable(${SERVER_NAME} RpgGameServer.cpp)
add_executable(${CLIENT_NAME} RpgGameClient.cpp)

target_link_libraries(${SERVER_NAME} PUBLIC ${GAME_COMMANDS})
target_link_libraries(${CLIENT_NAME} PUBLIC ${GAME_OBJECTS})

install(FILES config.txt DESTINATION ${CMAKE_INSTALL_PREFIX}/Assets)
install(FILES config.txt DESTINATION ${CMAKE_DEBUG_LOC}/Assets)

target_include_directories(${SERVER_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(${CLIENT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS ${SERVER_NAME} ${CLIENT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})